#pragma once
#include "Actor.h"

class IEnemy : public Actor {
public:
	IEnemy() {}
	IEnemy(VECTOR3 pos, float rotY) : Actor(pos, rotY) {}
	virtual ~IEnemy() {}
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool CollideWeapon(Actor* other, VECTOR3 btm, VECTOR3 top);
	virtual void OnDamage(Actor* other) {} // ダメージを受けたときの処理
protected:
	struct Capsule {
		VECTOR3 p1;
		VECTOR3 p2;
		float rad;
		Capsule() {
			p1 = VECTOR3(0,0,0);
			p2 = p1;
			rad = 0.0f;
		}
	};
	Capsule capsule;
};