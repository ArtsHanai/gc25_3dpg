#pragma once
#include "IEnemy.h"
#include "Animator.h"

class Goblin : public IEnemy {
public:
	Goblin(VECTOR3 pos, float rotY);
	~Goblin();
	void Update() override;
//	void Draw() override;
	void OnDamage(Actor* other) override;
private:
	enum AnimID {
		aNeutral = 0,
		aRun,
		aDamage = 10,
		aBlowIn,
		aBlowLoop,
		aBlowOut,
		aDown
	};
	int hp;

	enum State {
		sNormal,
		sDamage,
		sBlow,
	};
	State state;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateBlow();
	int blowAnim;

	VECTOR3 velocity; // ˆÚ“®ƒxƒNƒgƒ‹
};