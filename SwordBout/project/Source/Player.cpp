#include "Player.h"
#include "Camera.h"
#include "Pad.h"
#include "Stage.h"

Player::Player(VECTOR3 pos, float rotY)
{
	transform.position = pos;
	transform.rotation.y = rotY;

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
	if (true) {
		VECTOR2 stick = Pad::GetLStick();
		VECTOR3 in = VECTOR3(stick.x, 0, stick.y);	
		if (VSize(in) > 1.0f) {
			in = VNorm(in);
		}
		if (VSize(in) >= 0.2f) {
			VECTOR3 move = in * MGetRotY(camRot.y); // 進みたいベクトル
			float cosT = VDot(transform.Forward(), move); // 間の角のcos
			float th = acosf(cosT)*RadToDeg;
			if (acosf(cosT) <= 20.0f * DegToRad) { // 正面を向いてる
				transform.position += move * 200.0f * Time::DeltaTime();
				transform.rotation.y = atan2(move.x, move.z);
			} else {
				if (VDot(transform.Right(), move) > 0) {
					transform.rotation.y += 10.0f * DegToRad;
				} else {
					transform.rotation.y -= 10.0f * DegToRad;
				}
			}
		}
	}

	// 地面に接地
	Stage* st = FindGameObject<Stage>();
	VECTOR3 hitPos;
	if (st->FindGround(transform.position + VECTOR3(0, 200, 0),
		transform.position + VECTOR3(0, -200, 0), &hitPos)) {
		transform.position = hitPos;
	}
}
