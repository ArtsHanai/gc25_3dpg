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
	territory.center = pos;
	territory.range = 1000.0f; // cm
	route.clear();
	route.push_back(territory.center);
}

Goblin::~Goblin()
{
}

void Goblin::Update()
{
	IEnemy::Update();
	if (nextState != state) {
		delete action;
		action = nullptr;
		state = nextState;
	}
	switch (state) {
	case sNormal: UpdateNormal(); break;
	case sDamage: UpdateDamage(); break;
	case sBlow: UpdateBlow(); break;
	case sAttack: UpdateAttack(); break;
	case sLooking : UpdateLooking(); break;
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
			ChangeState(sDamage);
		} else {
			anim->Play(aBlowIn);
			ChangeState(sDamage);
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

void Goblin::SetRoute(std::vector<VECTOR3> points)
{
	route = points;
	route.push_back(territory.center);
}

void Goblin::UpdateNormal()
{
	VECTOR3 v = route[routeIdx] - transform.position;
	v.y = 0; // 高さを無視
	float lenMax = VSize(v); // 自分が移動するべき最大距離
	float rate = 1.0f;
	if (lenMax != 0) {
		float lenMove = 100.0f / Time::DeltaTime(); // 自分が移動する距離
		rate = lenMove / lenMax;
		if (rate >= 1.0f)
			rate = 1.0f;
		transform.position = Lerp<VECTOR3>(transform.position,
			route[routeIdx], rate);
		transform.rotation.y = atan2(v.x, v.z);
	}
	if (rate >= 1.0f) {
		routeIdx++;
		if (routeIdx >= route.size())
			routeIdx = 0;
	}
	if (InSight(500.0f, 30.0f * DegToRad)) {
		ChangeState(sAttack);
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
		ChangeState(sNormal);
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
	if (action == nullptr) { // 初回だけ
		action = new ActionApproach(this);
	}
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
		ChangeState(sNormal);
	}
}

void Goblin::UpdateLooking()
{
	VECTOR3 v = territory.center - transform.position;
	if (VSize(v) < 100.0f) {
		ChangeState(sNormal);
	}
	v = VNorm(v);
	transform.position += v*100.0f * Time::DeltaTime();
	transform.rotation.y = atan2(v.x, v.z);
}

void Goblin::ChangeState(State st)
{
	nextState = st;
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
	Player* p = FindGameObject<Player>();
	VECTOR3 v = p->GetTransform().position - owner->transform.position;
	v = VNorm(v);
	owner->transform.position += v * 100.0f * Time::DeltaTime();
	owner->transform.rotation.y = atan2(v.x, v.z);

	// テリトリーの範囲をチェック
	float d = owner->transform.Distance(owner->territory.center);
	if (d >= owner->territory.range) {
		owner->ChangeState(sLooking);
		return false;
	}
	// プレイヤーとの距離が１ｍ以内になったらtrue
	float dist = owner->transform.Distance(p->GetTransform().position);
	return (dist <= 100.0f);
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
