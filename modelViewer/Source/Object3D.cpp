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
	MATRIX mRotX = MGetRotX(transform.rotation.x);
	MATRIX mRotY = MGetRotY(transform.rotation.y);
	MATRIX mRotZ = MGetRotZ(transform.rotation.z);
	MATRIX mTrans = MGetTranslate(transform.position);
	MATRIX m = mRotZ * mRotX * mRotY * mTrans;
	MV1SetMatrix(hModel, m);
	MV1DrawModel(hModel);
}