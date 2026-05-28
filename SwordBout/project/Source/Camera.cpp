#include "Camera.h"
#include "Player.h"

Camera::Camera()
{
	transform.rotation.x = 10.0f * DegToRad;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	VECTOR3& rot = transform.rotation;
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		rot.y += 180.0f * Time::DeltaTime() * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		rot.y -= 180.0f * Time::DeltaTime() * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_UP)) {
		rot.x += 180.0f * Time::DeltaTime() * DegToRad;
		static const float UpLimit = 89.0f * DegToRad;
		if (rot.x >= UpLimit) {
			rot.x = UpLimit;
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		rot.x -= 180.0f * Time::DeltaTime() * DegToRad;
		static const float DownLimit = -45.0f * DegToRad;
		if (rot.x <= DownLimit) {
			rot.x = DownLimit;
		}
	}
}

void Camera::Draw()
{
	Player* p = FindGameObject<Player>();
	VECTOR3 playerPos = p->GetTransform().position;

	VECTOR3 camPos = VECTOR3(0, 0, -330) 
							* MGetRotX(transform.rotation.x)
							* MGetRotY(transform.rotation.y)
					+ playerPos + VECTOR3(0,150,0);
	SetCameraPositionAndTarget_UpVecY(camPos, playerPos + VECTOR3(0, 200, 0));
}
