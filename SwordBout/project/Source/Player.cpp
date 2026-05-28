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
	VECTOR3 move = VECTOR3(0,0,200.0f) * MGetRotY(camRot.y);
	if (CheckHitKey(KEY_INPUT_W)) {
		transform.position +=  move * Time::DeltaTime();
	}
}
