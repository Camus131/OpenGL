#pragma once


class ShaderProgram;
class Texture2D;

class RenderState
{
public:
	RenderState();
	~RenderState();

	//������ɫ����
	void SetShaderProgram(ShaderProgram* shader_program) { shader_program_ = shader_program; }

	//��ȡ��ɫ����
	ShaderProgram* GetShaderProgram()const { return shader_program_; }

	//��������������
	void SetDiffuseTexture(Texture2D* texture) { diffuse_texture_ = texture; }

	//��ȡ����������
	Texture2D* GetDiffuseTexture()const { return diffuse_texture_; }

	//���þ��������
	void SetSpecularTexture(Texture2D* texture) { specular_texture_ = texture; }

	//��ȡ���������
	Texture2D* GetSpecularTexture()const { return specular_texture_; }

private:
	ShaderProgram* shader_program_;

	Texture2D* diffuse_texture_;

	Texture2D* specular_texture_;
};