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

	//���붥����ɫ��
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
	glCompileShader(vertexShader);
	CheckError(vertexShader, 0);

	//����ƬԪ��ɫ��
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
	glCompileShader(fragmentShader);
	CheckError(fragmentShader, 1);

	//���뼸����ɫ��
	if (geometryShaderCode)
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometryShaderCode, nullptr);
		glCompileShader(geometryShader);
		CheckError(geometryShader, 2);
	}

	//������ɫ����
	id_ = glCreateProgram();
	glAttachShader(id_, vertexShader);
	glAttachShader(id_, fragmentShader);
	if (geometryShaderCode)
		glAttachShader(id_, geometryShader);
	glLinkProgram(id_);
	CheckError(id_, 3);

	//ɾ����ɫ��
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


void ShaderProgram::SetUniformMat4x4(const char* name, const float* value)
{
	glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE, value);
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
			std::cout << "������ɫ������ʧ��!\n" << infoLog << std::endl;
		}
	}break;
	case 1:
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "ƬԪ��ɫ������ʧ��!\n" << infoLog << std::endl;
		}
	}break;
	case 2:
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "������ɫ������ʧ��!\n" << infoLog << std::endl;
		}
	}break;
	case 3:
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "��ɫ��������ʧ��!\n" << infoLog << std::endl;
		}
	}break;
	}
}