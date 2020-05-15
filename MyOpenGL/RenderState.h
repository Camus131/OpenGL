#pragma once


class ShaderProgram;
class Texture2D;

class RenderState
{
public:
	RenderState();
	~RenderState();

	//设置着色程序
	void SetShaderProgram(ShaderProgram* shader_program) { shader_program_ = shader_program; }

	//获取着色程序
	ShaderProgram* GetShaderProgram()const { return shader_program_; }

	//设置漫反射纹理
	void SetDiffuseTexture(Texture2D* texture) { diffuse_texture_ = texture; }

	//获取漫反射纹理
	Texture2D* GetDiffuseTexture()const { return diffuse_texture_; }

	//设置镜面光纹理
	void SetSpecularTexture(Texture2D* texture) { specular_texture_ = texture; }

	//获取镜面光纹理
	Texture2D* GetSpecularTexture()const { return specular_texture_; }

private:
	ShaderProgram* shader_program_;

	Texture2D* diffuse_texture_;

	Texture2D* specular_texture_;
};