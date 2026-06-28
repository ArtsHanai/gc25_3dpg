#include "Goblin.h"
#include <assert.h>
#include "Stage.h"
#include "Player.h"

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
	anim->AddFile(aAttack, "data/models/Character/Goblin/Anim_Attack1.mv1", false);
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
	case sAttack: UpdateAttack(); break;
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
			velocity *= -BlowH; // 水平方向の移動 
			velocity.y = BlowV; // ジャンプの初速 
		}
	}

//	other->GetTransform()
//	DestroyMe();
}

void Goblin::UpdateNormal()
{
	if (InSight(500.0f, 30.0f * DegToRad)) {
		state = sAttack;
		action = new ActionApproach(this);
	}
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

void Goblin::UpdateAttack()
{
	if (action != nullptr) {
		if (action->Update()) {
			if (action->ID() == "Approach") {
				delete action;
				action = new ActionAttack(this);
			} else {
				delete action;
				action = new ActionApproach(this);
			}
		}
	}
	OutputDebugString(action->ID().c_str());
	// 視野から外れたらNormalにする
	if (!InSight(550.0f, 35.0f * DegToRad)) {
		state = sNormal;
	}
}

bool Goblin::InSight(float dist, float ang)
{
	// プレイヤーへのベクトルを作る
	Player* player = FindGameObject<Player>();
	VECTOR3 pPos = player->GetTransform().position;
	VECTOR3 v = pPos - transform.position;
	// その長さがdistよりも長ければreturn false;
	if (VSize(v) > dist)
		return false;
	// 自分の視野角に入っていればreturn true;
	v = VNorm(v);
	if (VDot(transform.Forward(), v) > cosf(ang)) {
		return true;
	}
	return false;
}

Goblin::ActionApproach::ActionApproach(Goblin* gob) : StateBase(gob)
{
}

Goblin::ActionApproach::~ActionApproach()
{
}

bool Goblin::ActionApproach::Update()
{
	// プレイヤーに近づく
	// プレイヤーとの距離が１ｍ以内になったらtrue
	owner->transform.position;
	return false;
}

Goblin::ActionAttack::ActionAttack(Goblin* gob) : StateBase(gob)
{
	owner->anim->Play(Goblin::AnimID::aAttack);
}

Goblin::ActionAttack::~ActionAttack()
{
}

bool Goblin::ActionAttack::Update()
{
	// 攻撃アクションが終わったらtrue
	if (owner->anim->IsFinish()) {
		return true;
	}
	return false;
}
