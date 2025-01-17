#pragma once

#include <cmath>


const float PI = 3.141592f;
const float PI_2 = 1.570796f;
const float PI_4 = 0.785398f;

inline float Angle(float rad) { return rad * 180.0f / PI; }
inline float Rad(float angle) { return angle * PI / 180.0f; }
inline float Cos(float angle) { return cosf(Rad(angle)); }
inline float Sin(float angle) { return sinf(Rad(angle)); }
inline float Tan(float angle) { return tanf(Rad(angle)); }
inline float Cot(float angle) { return 1.0f / Tan(angle); }