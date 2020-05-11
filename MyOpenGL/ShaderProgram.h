#pragma once


class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometryShaderCode = nullptr);
	~ShaderProgram();

	//������ɫ��
	void SetShaders(const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometryShaderCode = nullptr);

	//ɾ����ɫ����
	void DeleteProgram();

	//�Ƿ����
	bool IsActive() { return id_ != 0; }

	//������ɫ����
	void Use();

	//����Uniform����
	void SetUniformFloat(const char* name, float value);
	void SetUniformMat4x4(const char* name, const float* value);

private:
	//���������Ϣ
	void CheckError(unsigned int shader, int type);

private:
	unsigned int id_;
};