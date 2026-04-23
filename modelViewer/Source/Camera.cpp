#include "Camera.h"

Camera::Camera()
{
	transform.position = VECTOR3(0, 0, -300);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		transform.rotation.y -= 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		transform.rotation.x += 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_UP)) {
		transform.rotation.x -= 3.0f * DegToRad;
	}

	//transform.position を更新する
	static const VECTOR3 base = VECTOR3(0, 200, -300);
	MATRIX mRotX = MGetRotX(transform.rotation.x);
	MATRIX mRotY = MGetRotY(transform.rotation.y);	
	transform.position = base * mRotX * mRotY;
}

void Camera::Draw()
{
	SetCameraPositionAndTarget_UpVecY(transform.position, VECTOR3(0, 0, 0));
}
