#pragma once
#include <DxLib.h>

class VECTOR3 : public VECTOR
{
public:
	VECTOR3() : VECTOR3(0,0,0) {}
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

	const float DegToRad = DX_PI_F / 180.0f;
	const float RedToDeg = 180.0f / DX_PI_F;
};