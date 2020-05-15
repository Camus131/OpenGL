#pragma once

#include "Matrix4x4f.h"
#include "Vector2f.h"


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
	void SetUniformInt(const char* name, int value);
	void SetUniformMat4x4(const char* name, const Matrix4x4f& value);
	void SetUniformVec3(const char* name, const Vector3f& value);
	void SetUniformVec2(const char* name, const Vector2f& value);

private:
	//输出错误信息
	void CheckError(unsigned int shader, int type);

public:
	static const char* DefaultVertexShader;
	static const char* DefaultFragmentShader;
	static const char* InstancedVertexShader;

private:
	unsigned int id_;
};