#pragma once

#include "Matrix4x4f.h"
#include "Vector2f.h"

#include <vector>


class RenderState;

enum DrawMethod
{
	DrawArrays,
	DrawElements,
	DrawArraysInstanced,
	DrawElementsInstanced
};

struct Vertex
{
	Vector3f Postion;
	Vector3f Normal;
	Vector2f Texcoord;
	//Vector3f Tangent;
	//Vector3f Bitangent;
};


class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Vector3f> instanced);
	~Mesh();

	//设置渲染状态
	void SetState(RenderState* render_state) { render_state_ = render_state; }

	//获得渲染状态
	RenderState* GetState()const { return render_state_; }

	//设置模型矩阵
	void SetModelMatrix(const Matrix4x4f& model) { model_ = model; }

	//获得模型矩阵
	Matrix4x4f GetModelMatrix()const { return model_; }

	//设置绘制方式
	void SetDrawMethod(DrawMethod draw_method) { draw_method_ = draw_method; }

	//绘制
	void Draw();

private:
	void reset();
	void restinstanced();

private:
	unsigned int vao_;

	unsigned int vbo_;

	unsigned int ebo_;

	unsigned int instanced_vbo_;

	Matrix4x4f model_;

	RenderState* render_state_;

	//顶点数组
	std::vector<Vertex>	vertices_;

	//索引数组
	std::vector<unsigned int> indices_;

	//实例数组
	std::vector<Vector3f> instanced_;

	//绘制方式
	DrawMethod draw_method_;
};