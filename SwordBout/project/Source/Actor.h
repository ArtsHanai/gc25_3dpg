#pragma once
#include "Object3D.h"
#include "Animator.h"

class CapsuleCollider {
public:
	VECTOR3 pos1;
	VECTOR3 pos2;
	float rad;
	CapsuleCollider(VECTOR3 p1, VECTOR3 p2, float r)
		: pos1(p1), pos2(p2), rad(r)
	{
		pos1 += VECTOR3(0,r,0);
		pos2 -= VECTOR3(0,r,0);
	}
	CapsuleCollider() = delete;
};

class Actor : public Object3D {
public:
	Actor() : Actor(VECTOR3(0, 0, 0), 0) {}
	Actor(VECTOR3 pos, float rotY) {
		transform.position = pos;
		transform.rotation.y = rotY;
		anim = nullptr;
		capsule = nullptr;
	}
	virtual ~Actor() {
		if (anim != nullptr) {
			delete anim;
		}
		if (capsule != nullptr) {
			delete capsule;
		}
	}
	virtual void Update() override {
		if (anim != nullptr) {
			anim->Update();
		}
	}
//	virtual void Draw() override {}
protected:
	Animator* anim;
	int hWeapon;
	int weaponPoint;
	CapsuleCollider* capsule;
	void CollideStage();
};