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

	//������Ⱦ״̬
	void SetState(RenderState* render_state) { render_state_ = render_state; }

	//�����Ⱦ״̬
	RenderState* GetState()const { return render_state_; }

	//����ģ�;���
	void SetModelMatrix(const Matrix4x4f& model) { model_ = model; }

	//���ģ�;���
	Matrix4x4f GetModelMatrix()const { return model_; }

	//���û��Ʒ�ʽ
	void SetDrawMethod(DrawMethod draw_method) { draw_method_ = draw_method; }

	//����
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

	//��������
	std::vector<Vertex>	vertices_;

	//��������
	std::vector<unsigned int> indices_;

	//ʵ������
	std::vector<Vector3f> instanced_;

	//���Ʒ�ʽ
	DrawMethod draw_method_;
};