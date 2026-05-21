#include "Player.h"
#include "Stage.h"

Player::Player(const VECTOR3& pos)
{
	hModel = MV1LoadModel("data/models/WhiteChara.mv1");
	transform.position = pos;

	int root = MV1SearchFrame(hModel, "mini_simple_skeleton_demo");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(180.0f * DegToRad));

	// アニメーションの実験
	hAnim = MV1LoadModel("data/models/Anim_Run.mv1");
	attID = MV1AttachAnim(hModel, 0, hAnim);
	time = 0;
}

Player::~Player()
{
}

void Player::Update()
{
	// アニメーションの実験
	MV1SetAttachAnimTime(hModel, attID, time);
	time += 0.5;
	int max = MV1GetAnimTotalTime(hAnim, 0);
	if (time >= max) {
		time = 0;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		// 右旋回
		transform.rotation.y += 3*DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		// 左旋回
		transform.rotation.y -= 3 * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_W)) {
		// 前に移動
		transform.position += transform.Forward() * 2.0f;
	}
	Stage* st = FindGameObject<Stage>();
	transform.position += st->CollideSphere(
					transform.position+VECTOR3(0,50,0), 50);

//	float rotY = transform.rotation.y;
//	VECTOR3 camPos = VECTOR3(0, 0, -200)*MGetRotY(rotY)+transform.position;
	VECTOR3 camPos = transform.Forward() * -200 +
						transform.position + VECTOR3(0,200,0);;
	SetCameraPositionAndTarget_UpVecY(camPos, transform.position+VECTOR3(0,150, 0));
}
