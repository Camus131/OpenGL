#include "ShaderProgram.h"

#include "glad/glad.h"

#include <iostream>


ShaderProgram::ShaderProgram()
{
	id_ = 0;
}


ShaderProgram::ShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometryShaderCode)
{
	id_ = 0;
	SetShaders(vertexShaderCode, fragmentShaderCode, geometryShaderCode);
}


ShaderProgram::~ShaderProgram()
{
	DeleteProgram();
}


void ShaderProgram::SetShaders(const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometryShaderCode)
{
	DeleteProgram();
	unsigned int vertexShader, fragmentShader, geometryShader;

	//编译顶点着色器
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
	glCompileShader(vertexShader);
	CheckError(vertexShader, 0);

	//编译片元着色器
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
	glCompileShader(fragmentShader);
	CheckError(fragmentShader, 1);

	//编译几何着色器
	if (geometryShaderCode)
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometryShaderCode, nullptr);
		glCompileShader(geometryShader);
		CheckError(geometryShader, 2);
	}

	//链接着色程序
	id_ = glCreateProgram();
	glAttachShader(id_, vertexShader);
	glAttachShader(id_, fragmentShader);
	if (geometryShaderCode)
		glAttachShader(id_, geometryShader);
	glLinkProgram(id_);
	CheckError(id_, 3);

	//删除着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryShaderCode)
		glDeleteShader(geometryShader);
}


void ShaderProgram::DeleteProgram()
{
	if (id_)
	{
		glDeleteProgram(id_);
		id_ = 0;
	}
}


void ShaderProgram::Use()
{
	glUseProgram(id_);
}


void ShaderProgram::SetUniformFloat(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(id_, name), value);
}


void ShaderProgram::SetUniformInt(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(id_, name), value);
}


void ShaderProgram::SetUniformMat4x4(const char* name, const Matrix4x4f& value)
{
	glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE, value.GetPtr());
}


void ShaderProgram::SetUniformVec3(const char* name, const Vector3f& value)
{
	glUniform3fv(glGetUniformLocation(id_, name), 1, value.GetPtr());
}


void ShaderProgram::SetUniformVec2(const char* name, const Vector2f& value)
{
	glUniform2fv(glGetUniformLocation(id_, name), 1, value.GetPtr());
}


void ShaderProgram::CheckError(unsigned int shader, int type)
{
	int success;
	char infoLog[512];
	switch (type)
	{
	case 0:
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "顶点着色器编译失败!\n" << infoLog << std::endl;
		}
	}break;
	case 1:
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "片元着色器编译失败!\n" << infoLog << std::endl;
		}
	}break;
	case 2:
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "几何着色器编译失败!\n" << infoLog << std::endl;
		}
	}break;
	case 3:
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "着色程序链接失败!\n" << infoLog << std::endl;
		}
	}break;
	}
}

const char* ShaderProgram::DefaultVertexShader =
"#version 330 core\n"

"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 normal;\n"
"layout(location = 2) in vec3 texCoord;\n"

"out vec3 FragPos;\n"
"out vec3 Normal;\n"
"out vec2 TexCoord;\n"

"void main()\n"
"{\n"
"	FragPos = vec3(model * vec4(position, 1.0f));\n"
"	Normal = mat3(transpose(inverse(model))) * normal;\n"
"	TexCoord = vec2(texCoord.x, texCoord.y);\n"
"	gl_Position = projection * view * model * vec4(position, 1.0f);\n"
"}\0";

const char* ShaderProgram::InstancedVertexShader =
"#version 330 core\n"

"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 normal;\n"
"layout(location = 2) in vec3 texCoord;\n"
"layout(location = 3) in vec3 instanceInfo;\n"

"out vec3 FragPos;\n"
"out vec3 Normal;\n"
"out vec2 TexCoord;\n"

"void main()\n"
"{\n"
"   vec3 positionNew = instanceInfo + position;\n"
"	FragPos = vec3(model * vec4(positionNew, 1.0f));\n"
"	Normal = mat3(transpose(inverse(model))) * normal;\n"
"	TexCoord = vec2(texCoord.x, texCoord.y);\n"
"	gl_Position = projection * view * model * vec4(positionNew, 1.0f);\n"
"}\0";

const char* ShaderProgram::DefaultFragmentShader =
"#version 330 core\n"

"struct Material\n"
"{\n"
"	sampler2D diffuse;\n"
"	sampler2D specular;\n"
"	float shininess;\n"
"};\n"

"struct Light\n"
"{\n"
"	vec3 position;\n"
"	vec3 ambient;\n"
"	vec3 diffuse;\n"
"	vec3 specular;\n"
"};\n"

"uniform vec3 viewPos;\n"
"uniform Material material;\n"
"uniform Light light;\n"

"in vec3 FragPos;\n"
"in vec3 Normal;\n"
"in vec2 TexCoord;\n"

"out vec4 FragColor;\n"

"void main()\n"
"{\n"
"	vec3 normal = normalize(Normal);\n"

//环境光分量
"	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;\n"

//漫反射光分量
"	vec3 lightDir = normalize(light.position - FragPos);\n"
"	float diff = max(dot(normal, lightDir), 0.0f);\n"
"	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;\n"

//镜面光分量
"	vec3 viewDir = normalize(viewPos - FragPos);\n"
"	vec3 reflectDir = reflect(-lightDir, normal);\n"
"	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);\n"
"	vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;\n"

"	vec3 result = ambient + diffuse + specular;\n"
"	FragColor = vec4(result, 1.0);\n"
"}\0";