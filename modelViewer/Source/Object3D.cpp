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
	MV1SetRotationXYZ(hModel, VGet(0, 0, DX_PI_F / 6));
	MV1SetPosition(hModel, transform.position);
	MV1DrawModel(hModel);
}
