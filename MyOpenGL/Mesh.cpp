#include "Mesh.h"
#include "RenderState.h"
#include "Texture2D.h"

#include "glad/glad.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	vao_ = 0;
	vbo_ = 0;
	ebo_ = 0;
	model_.Identity();
	render_state_ = nullptr;
	vertices_ = vertices;
	indices_ = indices;
	draw_method_ = DrawElements;
	reset();
}


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Vector3f> instanced)
{
	vao_ = 0;
	vbo_ = 0;
	ebo_ = 0;
	instanced_vbo_ = 0;
	instanced_ = instanced;
	model_.Identity();
	render_state_ = nullptr;
	vertices_ = vertices;
	indices_ = indices;
	draw_method_ = DrawElementsInstanced;
	restinstanced();
}


Mesh::~Mesh()
{
	if (vao_)
	{
		glDeleteVertexArrays(1, &vao_);
		vao_ = 0;
	}
	if (vbo_)
	{
		glDeleteBuffers(1, &vbo_);
		vbo_ = 0;
	}
	if (ebo_)
	{
		glDeleteBuffers(1, &ebo_);
		ebo_ = 0;
	}

	if (instanced_vbo_)
	{
		glDeleteBuffers(1, &instanced_vbo_);
		instanced_vbo_ = 0;
	}
}


void Mesh::Draw()
{
	//绑定着色器
	//ShaderProgram* shader_program = render_state_->GetShaderProgram();
	//if (shader_program && shader_program->IsActive())
	//{
	//	shader_program->Use();
	//	shader_program->SetUniformMat4x4("model", model_.GetPtr());
	//}
	//else
	//{
	//	DefaultShaderProgram.Use();
	//	DefaultShaderProgram.SetUniformMat4x4("model", model_.GetPtr());
	//}

	//绑定纹理
	Texture2D* diffuse_texture = render_state_->GetDiffuseTexture();
	if (diffuse_texture && diffuse_texture->IsActive())
	{
		glActiveTexture(GL_TEXTURE0);
		diffuse_texture->Use();
	}

	Texture2D* specular_texture = render_state_->GetSpecularTexture();
	if (specular_texture && specular_texture->IsActive())
	{
		glActiveTexture(GL_TEXTURE1);
		specular_texture->Use();
	}

	//绑定VAO
	glBindVertexArray(vao_);
	switch (draw_method_)
	{
	case DrawElements:
		glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
		break;
	case DrawElementsInstanced:
		glDrawElementsInstanced(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0, instanced_.size());
	default:
		break;
	}

	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}


void Mesh::reset()
{
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), &vertices_[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Texcoord));

	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

	//glEnableVertexAttribArray(4);
	//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}


void Mesh::restinstanced()
{
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);
	glGenBuffers(1, &instanced_vbo_);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), &vertices_[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Texcoord));

	glBindBuffer(GL_ARRAY_BUFFER, instanced_vbo_);
	glBufferData(GL_ARRAY_BUFFER, instanced_.size() * sizeof(Vector3f), &instanced_[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), (void*)0);
	glVertexAttribDivisor(3, 1);

	glBindVertexArray(0);
}