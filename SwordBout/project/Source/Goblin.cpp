#include "Goblin.h"
#include <assert.h>
#include "Stage.h"

static const float BlowHigh = 200.0f;
static const float BlowFar = 300.0f;
static const float BlowG = 0.5f;

Goblin::Goblin(VECTOR3 pos, float rotY) : IEnemy(pos, rotY)
{
	hModel = MV1LoadModel("data/models/Character/Goblin/Goblin.mv1");
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	capsule.rad = 50.0f;
	capsule.p1 = VECTOR3(0, 50, 0);
	capsule.p2 = VECTOR3(0, 130,0);

	anim = new Animator(hModel);
	anim->AddFile(aNeutral, "data/models/Character/Goblin/Anim_Neutral.mv1", true);
	anim->AddFile(aRun, "data/models/Character/Goblin/Anim_Run.mv1", true);
	anim->AddFile(aDamage, "data/models/Character/Goblin/Anim_Damage.mv1", false);
	anim->AddFile(aBlowIn, "data/models/Character/Goblin/Anim_Blow_In.mv1", false);
	anim->AddFile(aBlowLoop, "data/models/Character/Goblin/Anim_Blow_Loop.mv1", true);
	anim->AddFile(aBlowOut, "data/models/Character/Goblin/Anim_Blow_Out.mv1", false);
	anim->AddFile(aDown, "data/models/Character/Goblin/Anim_Down_Loop.mv1", false);
	anim->Play(aNeutral);

	hp = 5;
}

Goblin::~Goblin()
{
}

void Goblin::Update()
{
	IEnemy::Update();
	switch (state) {
	case sNormal: UpdateNormal(); break;
	case sDamage: UpdateDamage(); break;
	case sBlow: UpdateBlow(); break;
	default: assert(false);
	}
}

void Goblin::OnDamage(Actor* other)
{
	// プレイヤーの方を向く
	VECTOR3 v = other->GetTransform().position;
	v -= transform.position;
	transform.rotation.y = atan2f(v.x, v.z);

	if (hp > 0) {
		hp--;
		if (hp > 0) {
			anim->Play(aDamage);
			state = sDamage;
		} else {
			anim->Play(aBlowIn);
			state = sBlow;
			blowAnim = 0;
			float BlowV = sqrtf(2.0f * BlowG * BlowHigh);
			float BlowH = BlowFar / (BlowV / BlowG) / 2.0f;
			velocity = VNorm(v);
			velocity *= -BlowH; // 水平方向の移動量
			velocity.y = BlowV; // ジャンプの初速
		}
	}

//	other->GetTransform()
//	DestroyMe();
}

void Goblin::UpdateNormal()
{
	Stage* st = FindGameObject<Stage>();
	VECTOR3 hit;
	if (st->FindGround(transform.position + VECTOR3(0, 100, 0), transform.position + VECTOR3(0, -100, 0), &hit)) {
		transform.position = hit;
	}
}

void Goblin::UpdateDamage()
{
	if (anim->IsFinish()) {
		state = sNormal;
		anim->Play(aNeutral);
	}
}

void Goblin::UpdateBlow()
{
	if (blowAnim == 0) {
		if (anim->IsFinish()) {
			anim->Play(aBlowLoop);
			blowAnim = 1;
		}
	}
	if (blowAnim < 2) {
		transform.position += velocity;
		velocity.y -= BlowG;
		Stage* st = FindGameObject<Stage>();
		VECTOR3 hit;
		if (st->FindGround(transform.position + VECTOR3(0, 100, 0), transform.position, &hit)) {
			transform.position = hit;
			anim->Play(aBlowOut);
			blowAnim = 2;
		}
	}
}
