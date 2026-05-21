#pragma once
#include <DxLib.h>

// ï‚ä‘ä÷êî
template <typename T>
T Lerp(T start, T end, float rate) {
	return (end - start) * rate + start;
}

class VECTOR3 : public VECTOR
{
public:
	VECTOR3() : VECTOR3(0, 0, 0) {}
	VECTOR3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	VECTOR3 operator +(const VECTOR3& v) {
		return VECTOR3(x + v.x, y + v.y, z + v.z);
	}
	VECTOR3& operator +=(const VECTOR3& v) {
		x += v.x; y += v.y;	z += v.z;
		return *this;
	}
	VECTOR3 operator -(const VECTOR3& v) {
		return VECTOR3(x - v.x, y - v.y, z - v.z);
	}
	VECTOR3& operator -=(const VECTOR3& v) {
		x -= v.x; y -= v.y;	z -= v.z;
		return *this;
	}
	VECTOR3 operator *(float s) {
		return VECTOR3(x * s, y * s, z * s);
	}
	VECTOR3& operator *=(float s) {
		x *= s; y *= s;	z *= s;
		return *this;
	}
	VECTOR3 operator /(float s) {
		return VECTOR3(x / s, y / s, z / s);
	}
	VECTOR3& operator /=(float s) {
		x /= s; y /= s;	z /= s;
		return *this;
	}
	VECTOR3(VECTOR v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}
	VECTOR3 operator *(const MATRIX& m)
	{
		return VTransform(*this, m);
	}
};

const float DegToRad = DX_PI_F / 180.0f;
const float RedToDeg = 180.0f / DX_PI_F;

inline MATRIX operator *(const MATRIX& m1, const MATRIX& m2)
{
	return MMult(m1, m2);
};
inline MATRIX& operator *=(MATRIX& m1, const MATRIX& m2)
{
	return m1 = m1 * m2;
};

inline VECTOR operator *(const VECTOR& v, const MATRIX& m)
{
	return VTransform(v, m);
}

inline VECTOR operator *=(VECTOR& v, const MATRIX& m)
{
	return v = v * m;
}

static unsigned int C_WHITE = GetColor(255,255,255);
static unsigned int C_RED = GetColor(255, 0, 0);
static unsigned int C_BLUE = GetColor(0, 255, 0);
static unsigned int C_GREEN = GetColor(0, 0, 255);
static const VECTOR3 V_ZERO = VECTOR3(0, 0, 0);
