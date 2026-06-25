#include "Goblin.h"
#include <assert.h>

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
	if (hp > 0) {
		hp--;
		if (hp > 0) {
			anim->Play(aDamage);
			state = sDamage;
		} else {
			anim->Play(aBlowIn);
			state = sBlow;
			blowAnim = 0;
			// 吹き飛び死亡
		}
	}
//	other->GetTransform()
//	DestroyMe();
}

void Goblin::UpdateNormal()
{
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
	if (anim->IsFinish()) {
		anim->Play(aBlowLoop);
	}
}
