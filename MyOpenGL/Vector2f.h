#pragma once


class Vector2f
{
public:
	Vector2f() { v_[0] = 0.0f;v_[1] = 0.0f; }
	Vector2f(float x, float y) { v_[0] = x; v_[1] = y; }
	Vector2f(const Vector2f& v) { v_[0] = v.x();v_[1] = v.y(); }

	//获得地址
	float* GetPtr()const { return (float*)v_; }

	//取值
	float& x() { return v_[0]; }
	float& y() { return v_[1]; }
	float x()const { return v_[0]; }
	float y()const { return v_[1]; }

	//操作符重载
	Vector2f& operator=(const Vector2f& v) { v_[0] = v.x();v_[1] = v.y();return *this; }
	bool operator==(const Vector2f& v)const { return v_[0] == v.x() && v_[1] == v.y(); }
	bool operator!=(const Vector2f& v)const { return v_[0] != v.x() || v_[1] != v.y(); }
	Vector2f operator-()const { return Vector2f(-v_[0], -v_[1]); }
	Vector2f operator+(const Vector2f& v)const { return Vector2f(v_[0] + v.x(), v_[1] + v.y()); }
	Vector2f operator-(const Vector2f& v)const { return Vector2f(v_[0] - v.x(), v_[1] - v.y()); }
	Vector2f operator*(float k)const { return Vector2f(v_[0] * k, v_[1] * k); }
	Vector2f operator/(float k)const { float re_k = 1.0f / k;return Vector2f(v_[0] * re_k, v_[1] * re_k); }
	Vector2f& operator+=(const Vector2f& v) { v_[0] += v.x();v_[1] += v.y();return *this; }
	Vector2f& operator-=(const Vector2f& v) { v_[0] -= v.x();v_[1] -= v.y();return *this; }
	Vector2f& operator*=(float k) { v_[0] *= k;v_[1] *= k;return *this; }
	Vector2f& operator/=(float k) { float re_k = 1.0f / k;v_[0] *= re_k;v_[1] *= re_k;return *this; }

private:
	float v_[2];
};