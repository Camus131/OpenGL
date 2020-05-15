#pragma once

#include "Vector3f.h"



class Matrix4x4f
{
public:
	Matrix4x4f() { Identity(); }

	Matrix4x4f(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
		m_[0][0] = m00; m_[1][0] = m01; m_[2][0] = m02; m_[3][0] = m03;
		m_[0][1] = m10; m_[1][1] = m11; m_[2][1] = m12; m_[3][1] = m13;
		m_[0][2] = m20; m_[1][2] = m21; m_[2][2] = m22; m_[3][2] = m23;
		m_[0][3] = m30; m_[1][3] = m31; m_[2][3] = m32; m_[3][3] = m33;
	}

	Matrix4x4f(const Matrix4x4f& m)
	{
		m_[0][0] = m(0, 0); m_[1][0] = m(0, 1); m_[2][0] = m(0, 2); m_[3][0] = m(0, 3);
		m_[0][1] = m(1, 0); m_[1][1] = m(1, 1); m_[2][1] = m(1, 2); m_[3][1] = m(1, 3);
		m_[0][2] = m(2, 0); m_[1][2] = m(2, 1); m_[2][2] = m(2, 2); m_[3][2] = m(2, 3);
		m_[0][3] = m(3, 0); m_[1][3] = m(3, 1); m_[2][3] = m(3, 2); m_[3][3] = m(3, 3);
	}

	//单位化
	Matrix4x4f& Identity()
	{
		m_[0][0] = 1.0f; m_[1][0] = 0.0f; m_[2][0] = 0.0f; m_[3][0] = 0.0f;
		m_[0][1] = 0.0f; m_[1][1] = 1.0f; m_[2][1] = 0.0f; m_[3][1] = 0.0f;
		m_[0][2] = 0.0f; m_[1][2] = 0.0f; m_[2][2] = 1.0f; m_[3][2] = 0.0f;
		m_[0][3] = 0.0f; m_[1][3] = 0.0f; m_[2][3] = 0.0f; m_[3][3] = 1.0f;
		return *this;
	}

	//获得地址
	float* GetPtr()const { return (float*)m_; }

	//重载操作符
	float& operator()(int row, int col) { return m_[col][row]; }
	float operator()(int row, int col)const { return m_[col][row]; }

	Matrix4x4f& operator=(const Matrix4x4f& m)
	{
		m_[0][0] = m(0, 0); m_[1][0] = m(0, 1); m_[2][0] = m(0, 2); m_[3][0] = m(0, 3);
		m_[0][1] = m(1, 0); m_[1][1] = m(1, 1); m_[2][1] = m(1, 2); m_[3][1] = m(1, 3);
		m_[0][2] = m(2, 0); m_[1][2] = m(2, 1); m_[2][2] = m(2, 2); m_[3][2] = m(2, 3);
		m_[0][3] = m(3, 0); m_[1][3] = m(3, 1); m_[2][3] = m(3, 2); m_[3][3] = m(3, 3);
		return *this;
	}

	bool operator==(const Matrix4x4f& m)const
	{
		return 		m_[0][0] == m(0, 0) && m_[1][0] == m(0, 1) && m_[2][0] == m(0, 2) && m_[3][0] == m(0, 3) &&
			m_[0][1] == m(1, 0) && m_[1][1] == m(1, 1) && m_[2][1] == m(1, 2) && m_[3][1] == m(1, 3) &&
			m_[0][2] == m(2, 0) && m_[1][2] == m(2, 1) && m_[2][2] == m(2, 2) && m_[3][2] == m(2, 3) &&
			m_[0][3] == m(3, 0) && m_[1][3] == m(3, 1) && m_[2][3] == m(3, 2) && m_[3][3] == m(3, 3);
	}

	bool operator!=(const Matrix4x4f& m)const
	{
		return 		m_[0][0] != m(0, 0) || m_[1][0] != m(0, 1) || m_[2][0] != m(0, 2) || m_[3][0] != m(0, 3) ||
			m_[0][1] != m(1, 0) || m_[1][1] != m(1, 1) || m_[2][1] != m(1, 2) || m_[3][1] != m(1, 3) ||
			m_[0][2] != m(2, 0) || m_[1][2] != m(2, 1) || m_[2][2] != m(2, 2) || m_[3][2] != m(2, 3) ||
			m_[0][3] != m(3, 0) || m_[1][3] != m(3, 1) || m_[2][3] != m(3, 2) || m_[3][3] != m(3, 3);
	}

	Vector3f operator*(const Vector3f& v)const
	{
		float re = 1.0f / (m_[0][3] * v.x() + m_[1][3] * v.y() + m_[2][3] * v.z() + m_[3][3]);
		return Vector3f(
			re * (m_[0][0] * v.x() + m_[1][0] * v.y() + m_[2][0] * v.z() + m_[3][0]),
			re * (m_[0][1] * v.x() + m_[1][1] * v.y() + m_[2][1] * v.z() + m_[3][1]),
			re * (m_[0][2] * v.x() + m_[1][2] * v.y() + m_[2][2] * v.z() + m_[3][2])
		);
	}

	Matrix4x4f operator*(const Matrix4x4f& m)const
	{
		return Matrix4x4f(
			m_[0][0] * m(0, 0) + m_[1][0] * m(1, 0) + m_[2][0] * m(2, 0) + m_[3][0] * m(3, 0),
			m_[0][0] * m(0, 1) + m_[1][0] * m(1, 1) + m_[2][0] * m(2, 1) + m_[3][0] * m(3, 1),
			m_[0][0] * m(0, 2) + m_[1][0] * m(1, 2) + m_[2][0] * m(2, 2) + m_[3][0] * m(3, 2),
			m_[0][0] * m(0, 3) + m_[1][0] * m(1, 3) + m_[2][0] * m(2, 3) + m_[3][0] * m(3, 3),
			m_[0][1] * m(0, 0) + m_[1][1] * m(1, 0) + m_[2][1] * m(2, 0) + m_[3][1] * m(3, 0),
			m_[0][1] * m(0, 1) + m_[1][1] * m(1, 1) + m_[2][1] * m(2, 1) + m_[3][1] * m(3, 1),
			m_[0][1] * m(0, 2) + m_[1][1] * m(1, 2) + m_[2][1] * m(2, 2) + m_[3][1] * m(3, 2),
			m_[0][1] * m(0, 3) + m_[1][1] * m(1, 3) + m_[2][1] * m(2, 3) + m_[3][1] * m(3, 3),
			m_[0][2] * m(0, 0) + m_[1][2] * m(1, 0) + m_[2][2] * m(2, 0) + m_[3][2] * m(3, 0),
			m_[0][2] * m(0, 1) + m_[1][2] * m(1, 1) + m_[2][2] * m(2, 1) + m_[3][2] * m(3, 1),
			m_[0][2] * m(0, 2) + m_[1][2] * m(1, 2) + m_[2][2] * m(2, 2) + m_[3][2] * m(3, 2),
			m_[0][2] * m(0, 3) + m_[1][2] * m(1, 3) + m_[2][2] * m(2, 3) + m_[3][2] * m(3, 3),
			m_[0][3] * m(0, 0) + m_[1][3] * m(1, 0) + m_[2][3] * m(2, 0) + m_[3][3] * m(3, 0),
			m_[0][3] * m(0, 1) + m_[1][3] * m(1, 1) + m_[2][3] * m(2, 1) + m_[3][3] * m(3, 1),
			m_[0][3] * m(0, 2) + m_[1][3] * m(1, 2) + m_[2][3] * m(2, 2) + m_[3][3] * m(3, 2),
			m_[0][3] * m(0, 3) + m_[1][3] * m(1, 3) + m_[2][3] * m(2, 3) + m_[3][3] * m(3, 3)
		);
	}

	Matrix4x4f& operator*=(const Matrix4x4f& m)
	{
		float m00 = m_[0][0] * m(0, 0) + m_[1][0] * m(1, 0) + m_[2][0] * m(2, 0) + m_[3][0] * m(3, 0);
		float m01 = m_[0][0] * m(0, 1) + m_[1][0] * m(1, 1) + m_[2][0] * m(2, 1) + m_[3][0] * m(3, 1);
		float m02 = m_[0][0] * m(0, 2) + m_[1][0] * m(1, 2) + m_[2][0] * m(2, 2) + m_[3][0] * m(3, 2);
		float m03 = m_[0][0] * m(0, 3) + m_[1][0] * m(1, 3) + m_[2][0] * m(2, 3) + m_[3][0] * m(3, 3);
		float m10 = m_[0][1] * m(0, 0) + m_[1][1] * m(1, 0) + m_[2][1] * m(2, 0) + m_[3][1] * m(3, 0);
		float m11 = m_[0][1] * m(0, 1) + m_[1][1] * m(1, 1) + m_[2][1] * m(2, 1) + m_[3][1] * m(3, 1);
		float m12 = m_[0][1] * m(0, 2) + m_[1][1] * m(1, 2) + m_[2][1] * m(2, 2) + m_[3][1] * m(3, 2);
		float m13 = m_[0][1] * m(0, 3) + m_[1][1] * m(1, 3) + m_[2][1] * m(2, 3) + m_[3][1] * m(3, 3);
		float m20 = m_[0][2] * m(0, 0) + m_[1][2] * m(1, 0) + m_[2][2] * m(2, 0) + m_[3][2] * m(3, 0);
		float m21 = m_[0][2] * m(0, 1) + m_[1][2] * m(1, 1) + m_[2][2] * m(2, 1) + m_[3][2] * m(3, 1);
		float m22 = m_[0][2] * m(0, 2) + m_[1][2] * m(1, 2) + m_[2][2] * m(2, 2) + m_[3][2] * m(3, 2);
		float m23 = m_[0][2] * m(0, 3) + m_[1][2] * m(1, 3) + m_[2][2] * m(2, 3) + m_[3][2] * m(3, 3);
		float m30 = m_[0][3] * m(0, 0) + m_[1][3] * m(1, 0) + m_[2][3] * m(2, 0) + m_[3][3] * m(3, 0);
		float m31 = m_[0][3] * m(0, 1) + m_[1][3] * m(1, 1) + m_[2][3] * m(2, 1) + m_[3][3] * m(3, 1);
		float m32 = m_[0][3] * m(0, 2) + m_[1][3] * m(1, 2) + m_[2][3] * m(2, 2) + m_[3][3] * m(3, 2);
		float m33 = m_[0][3] * m(0, 3) + m_[1][3] * m(1, 3) + m_[2][3] * m(2, 3) + m_[3][3] * m(3, 3);
		m_[0][0] = m00; m_[1][0] = m01; m_[2][0] = m02; m_[3][0] = m03;
		m_[0][1] = m10; m_[1][1] = m11; m_[2][1] = m12; m_[3][1] = m13;
		m_[0][2] = m20; m_[1][2] = m21; m_[2][2] = m22; m_[3][2] = m23;
		m_[0][3] = m30; m_[1][3] = m31; m_[2][3] = m32; m_[3][3] = m33;
		return *this;
	}

	//平移矩阵
	static Matrix4x4f Translate(float x, float y, float z)
	{
		return Matrix4x4f(
			1.0f, 0.0f, 0.0f, x,
			0.0f, 1.0f, 0.0f, y,
			0.0f, 0.0f, 1.0f, z,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	//旋转矩阵
	static Matrix4x4f Rotate(float angle, const Vector3f& axis)
	{
		Vector3f a(axis);
		a.Normalize();
		float x = a.x();
		float y = a.y();
		float z = a.z();
		float c = Cos(angle);
		float s = Sin(angle);
		return Matrix4x4f(
			x * x * (1.0f - c) + c, x * y * (1.0f - c) - z * s, x * z * (1.0f - c) + y * s, 0.0f,
			x * y * (1.0f - c) + z * s, y * y * (1.0f - c) + c, y * z * (1.0f - c) - x * s, 0.0f,
			x * z * (1.0f - c) - y * s, y * z * (1.0f - c) + x * s, z * z * (1.0f - c) + c, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	//缩放矩阵
	static Matrix4x4f Scale(float x, float y, float z)
	{
		return Matrix4x4f(
			x, 0.0f, 0.0f, 0.0f,
			0.0f, y, 0.0f, 0.0f,
			0.0f, 0.0f, z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	//视图矩阵
	static Matrix4x4f LookAt(const Vector3f& position, const Vector3f& target, const Vector3f& up)
	{
		Vector3f b = position - target;
		Vector3f u(up);
		b.Normalize();
		u.Normalize();
		Vector3f r = Vector3f::CrossProduct(u, b);
		return Matrix4x4f(
			r.x(), r.y(), r.z(), 0.0f,
			u.x(), u.y(), u.z(), 0.0f,
			b.x(), b.y(), b.z(), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		) * Translate(-position.x(), -position.y(), -position.z());
	}

	//正交投影矩阵
	static Matrix4x4f Ortho(float left, float right, float bottom, float top, float near, float far)
	{
		return Matrix4x4f(
			2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left),
			0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom),
			0.0f, 0.0f, -2.0f / (far - near), -(far + near) / (far - near),
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	//透视投影矩阵
	static Matrix4x4f Perspective(float left, float right, float bottom, float top, float near, float far)
	{
		return Matrix4x4f(
			2 * near / (right - left), 0.0f, (right + left) / (right - left), 0.0f,
			0.0f, 2 * near / (top - bottom), (top + bottom) / (top - bottom), 0.0f,
			0.0f, 0.0f, -(far + near) / (far - near), -2 * far * near / (far - near),
			0.0f, 0.0f, -1.0f, 0.0f
		);
	}

	//透视投影矩阵(fov)
	static Matrix4x4f PerspectiveFov(float fovy, float aspect, float near, float far)
	{
		float cot = Cot(fovy / 2);
		return Matrix4x4f(
			cot / aspect, 0.0f, 0.0f, 0.0f,
			0.0f, cot, 0.0f, 0.0f,
			0.0f, 0.0f, -(far + near) / (far - near), -2 * far * near / (far - near),
			0.0f, 0.0f, -1.0f, 0.0f
		);
	}

private:
	float m_[4][4];
};