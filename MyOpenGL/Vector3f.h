#pragma once

#include "Math.h"


class Vector3f
{
public:
	Vector3f() { v_[0] = 0.0f;v_[1] = 0.0f;v_[2] = 0.0f; }
	Vector3f(float x, float y, float z) { v_[0] = x; v_[1] = y; v_[2] = z; }
	Vector3f(const Vector3f& v) { v_[0] = v.x();v_[1] = v.y();v_[2] = v.z(); }

	//置零
	Vector3f& Zero() { v_[0] = 0.0f;v_[1] = 0.0f;v_[2] = 0.0f;return *this; }

	//求模
	float Mod() { return sqrtf(v_[0] * v_[0] + v_[1] * v_[1] + v_[2] * v_[2]); }

	//单位化
	Vector3f& Normalize()
	{
		float mod = Mod();
		if (mod > 0.0f)
		{
			float re_mod = 1.0f / mod;
			v_[0] *= re_mod;
			v_[1] *= re_mod;
			v_[2] *= re_mod;
		}
		return *this;
	}

	//获得地址
	float* GetPtr()const { return (float*)v_; }

	//取值
	float& x() { return v_[0]; }
	float& y() { return v_[1]; }
	float& z() { return v_[2]; }
	float x()const { return v_[0]; }
	float y()const { return v_[1]; }
	float z()const { return v_[2]; }

	//操作符重载
	Vector3f& operator=(const Vector3f& v) { v_[0] = v.x();v_[1] = v.y();v_[2] = v.z();return *this; }
	bool operator==(const Vector3f& v)const { return v_[0] == v.x() && v_[1] == v.y() && v_[2] == v.z(); }
	bool operator!=(const Vector3f& v)const { return v_[0] != v.x() || v_[1] != v.y() || v_[2] != v.z(); }
	Vector3f operator-()const { return Vector3f(-v_[0], -v_[1], -v_[2]); }
	Vector3f operator+(const Vector3f& v)const { return Vector3f(v_[0] + v.x(), v_[1] + v.y(), v_[2] + v.z()); }
	Vector3f operator-(const Vector3f& v)const { return Vector3f(v_[0] - v.x(), v_[1] - v.y(), v_[2] - v.z()); }
	Vector3f operator*(float k)const { return Vector3f(v_[0] * k, v_[1] * k, v_[2] * k); }
	Vector3f operator/(float k)const { float re_k = 1.0f / k;return Vector3f(v_[0] * re_k, v_[1] * re_k, v_[2] * re_k); }
	Vector3f& operator+=(const Vector3f& v) { v_[0] += v.x();v_[1] += v.y();v_[2] += v.z();return *this; }
	Vector3f& operator-=(const Vector3f& v) { v_[0] -= v.x();v_[1] -= v.y();v_[2] -= v.z();return *this; }
	Vector3f& operator*=(float k) { v_[0] *= k;v_[1] *= k;v_[2] *= k;return *this; }
	Vector3f& operator/=(float k) { float re_k = 1.0f / k;v_[0] *= re_k;v_[1] *= re_k;v_[2] *= re_k;return *this; }
	float operator*(const Vector3f& v)const { return v_[0] * v.x() + v_[1] * v.y() + v_[2] * v.z(); }

	//叉乘
	static Vector3f CrossProduct(const Vector3f& v1, const Vector3f& v2) { return Vector3f(v1.y() * v2.z() - v1.z() * v2.y(), v1.z() * v2.x() - v1.x() * v2.z(), v1.x() * v2.y() - v1.y() * v2.x()); }

	//距离
	static float Distance(const Vector3f& v1, const Vector3f& v2)
	{
		float dx = v1.x() - v2.x();
		float dy = v1.y() - v2.y();
		float dz = v1.z() - v2.z();
		return sqrtf(dx * dx + dy * dy + dz * dz);
	}

private:
	float v_[3];
};