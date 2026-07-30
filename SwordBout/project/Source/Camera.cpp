#include "Camera.h"
#include "Player.h"
#include "Pad.h"
#include "Stage.h"

Camera::Camera()
{
	transform.rotation.x = 10.0f * DegToRad;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	Pad* pad = FindGameObject<Pad>();
	VECTOR3& rot = transform.rotation;
	// 右スティックの値を返してもらって、カメラを動かす
	float stickX = pad->GetRStickX();
	rot.y += stickX * 180.0f * Time::DeltaTime() * DegToRad;
	float stickY = pad->GetRStickY();
	rot.x += stickY * 180.0f * Time::DeltaTime() * DegToRad;
	static const float UpLimit = 89.0f * DegToRad;
	static const float DownLimit = -45.0f * DegToRad;
	rot.x = min(rot.x, UpLimit);
	rot.x = max(rot.x, DownLimit);

	Player* p = FindGameObject<Player>();
	VECTOR3 playerPos = p->GetTransform().position;
	VECTOR3 center = playerPos + VECTOR3(0, 150, 0);
	MATRIX mat = MGetRotX(transform.rotation.x)
		* MGetRotY(transform.rotation.y);
	VECTOR3 camPos = VECTOR3(0, 0, -330) * mat + center;

	Stage* st = FindGameObject<Stage>();
	VECTOR3 hitPos;
	if (st->FindGround(center, camPos, &hitPos)) {
		camPos = hitPos;
	}

	if (CheckHitKey(KEY_INPUT_P)) {
		SetCameraPositionAndTarget_UpVecY(camPos + VECTOR3(0, 6000, 0), playerPos + VECTOR3(0, 200, 0));
	} else {
		SetCameraPositionAndTarget_UpVecY(camPos, playerPos + VECTOR3(0, 200, 0));
	}
}

void Camera::Draw()
{
}
