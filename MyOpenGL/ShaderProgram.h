#pragma once


class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometryShaderCode = nullptr);
	~ShaderProgram();

	//设置着色器
	void SetShaders(const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometryShaderCode = nullptr);

	//删除着色程序
	void DeleteProgram();

	//是否可用
	bool IsActive() { return id_ != 0; }

	//激活着色程序
	void Use();

	//设置Uniform变量
	void SetUniformFloat(const char* name, float value);
	void SetUniformMat4x4(const char* name, const float* value);

private:
	//输出错误信息
	void CheckError(unsigned int shader, int type);

private:
	unsigned int id_;
};