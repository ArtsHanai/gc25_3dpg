#include "Object3D.h"

Object3D::Object3D()
{
	hModel = -1;
}

Object3D::~Object3D()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
	}
}

void Object3D::Draw()
{
	MATRIX mRot = transform.rotation.Matrix();
	MATRIX mTrans = MGetTranslate(transform.position);
	MATRIX m = mRot * mTrans;
	MV1SetMatrix(hModel, m);
	MV1DrawModel(hModel);
}

Rotation::Rotation()
{
	rot = MGetIdent();
}

Rotation::~Rotation()
{
}

void Rotation::SetRot(float x, float y, float z)
{
	MATRIX rotX = MGetRotX(x);
	MATRIX rotY = MGetRotY(y);
	MATRIX rotZ = MGetRotZ(z);
	rot = rotZ * rotX * rotY;
}

VECTOR3 Rotation::GetRot()
{
	return VECTOR3();
}

void Rotation::RotX(float x)
{
	MATRIX m = MGetRotX(x);
	rot *= m;
}

void Rotation::RotY(float y)
{
	MATRIX m = MGetRotY(y);
	rot *= m;
}

void Rotation::RotZ(float z)
{
	MATRIX m = MGetRotZ(z);
	rot *= m;
}

void Rotation::RotAxis(VECTOR3 axis, float r)
{
	rot *= MGetRotAxis(axis, r);
}
