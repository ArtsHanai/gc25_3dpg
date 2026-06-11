#include "Player.h"
#include "Camera.h"
#include "Pad.h"
#include "Stage.h"
#include <assert.h>

Player::Player(VECTOR3 pos, float rotY)
{
	transform.position = pos;
	transform.rotation.y = rotY;

	hModel = MV1LoadModel("data/models/Character/Player/PC.mv1");
//	MV1SetFrameUserLocalMatrix(hModel, 15, MGetRotY(DX_PI_F));
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	anim = new Animator(hModel);
	anim->AddFile(0, "data/models/Character/Player/Anim_Neutral.mv1", true);
	anim->AddFile(1, "data/models/Character/Player/Anim_Run.mv1", true);
	anim->AddFile(2, "data/models/Character/Player/Anim_Attack1.mv1", false);
	anim->AddFile(3, "data/models/Character/Player/Anim_Attack2.mv1", false);
	anim->AddFile(4, "data/models/Character/Player/Anim_Attack3.mv1", false);
	anim->Play(0);

	hWeapon = MV1LoadModel("data/models/Character/Weapon/Sabel/Sabel.mv1");

	state = State::sNormal;
}

Player::~Player()
{
	delete anim;
}

void Player::Update()
{
	anim->Update();
	switch (state) {
	case sNormal:  UpdateNormal();  break;
	case sAttack1: UpdateAttack1();	break;
	case sAttack2: UpdateAttack2();	break;
	case sAttack3: UpdateAttack3();	break;
	case sDamage:  UpdateDamage();  break;
	default: assert(false);
	}
	// 地面に接地
	Stage* st = FindGameObject<Stage>();
	VECTOR3 hitPos;
	if (st->FindGround(transform.position + VECTOR3(0, 200, 0),
		transform.position + VECTOR3(0, -200, 0), &hitPos)) {
		transform.position = hitPos;
	}
}

void Player::Draw()
{
	Object3D::Draw();

	int wp = MV1SearchFrame(hModel, "wp");
	MATRIX mat = MV1GetFrameLocalWorldMatrix(hModel, wp);
	MV1SetMatrix(hWeapon, mat);
	MV1DrawModel(hWeapon);

	DrawLine3D(VECTOR3(0, 0, 0)*mat, VECTOR3(0, -100, 0)*mat,
			GetColor(255,0,0));
}

void Player::UpdateNormal()
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
			float th = acosf(cosT) * RadToDeg;
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
			anim->Play(1);
		} else {
			anim->Play(0);
		}
	}
	if (Pad::OnPush(Pad::ATTACK)) {
		state = State::sAttack1;
		attackPushed = false;
	}
}

void Player::UpdateAttack1()
{
	anim->Play(2);
	if (anim->IsFinish()) {
		state = State::sNormal;
	} else if (anim->GetCurrentFrame() <= 8.5f) {
		if (Pad::OnPush(Pad::ATTACK)) {
			attackPushed = true;
		}
	} else {
		if (attackPushed) {
			state = State::sAttack2;
			attackPushed = false;
		}
	}
}

void Player::UpdateAttack2()
{
	anim->Play(3);
	if (anim->IsFinish()) {
		state = State::sNormal;
	} else if (anim->GetCurrentFrame() <= 9.5f) {
		if (Pad::OnPush(Pad::ATTACK)) {
			attackPushed = true;
		}
	} else {
		if (attackPushed) {
			state = State::sAttack3;
			attackPushed = false;
		}
	}
}

void Player::UpdateAttack3()
{
	anim->Play(4);
	if (anim->IsFinish()) {
		state = State::sNormal;
	}
}

void Player::UpdateDamage()
{
}
