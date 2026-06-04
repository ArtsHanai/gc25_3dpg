#include "Player.h"
#include "Camera.h"

Player::Player()
{
	hModel = MV1LoadModel("data/models/Character/Player/PC.mv1");
//	MV1SetFrameUserLocalMatrix(hModel, 15, MGetRotY(DX_PI_F));
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));
}

Player::~Player()
{
}

void Player::Update()
{
	Camera* cam = FindGameObject<Camera>();
	VECTOR3 camRot = cam->GetTransform().rotation;
	float myRot = transform.rotation.y;
	if (CheckHitKey(KEY_INPUT_W)) {
		VECTOR3 move = VECTOR3(0, 0, 1) * MGetRotY(camRot.y); // 進みたいベクトル
		float cosT = VDot(transform.Forward(), move); // 間の角のcos
		if (acosf(cosT) < 20.0f * DegToRad) { // 正面を向いてる
			transform.position += move * 200.0f * Time::DeltaTime();
			transform.rotation.y = atan2(move.x, move.z);
		} else {
			if (VDot(transform.Right(), move) > 0) {
				transform.rotation.y += 20.0f * DegToRad;
			} else {
				transform.rotation.y -= 20.0f * DegToRad;
			}
		}
	}
}
