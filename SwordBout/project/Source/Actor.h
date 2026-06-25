#pragma once
#include "Object3D.h"
#include "Animator.h"

class Actor : public Object3D {
public:
	Actor() : Actor(VECTOR3(0, 0, 0), 0) {}
	Actor(VECTOR3 pos, float rotY) {
		transform.position = pos;
		transform.rotation.y = rotY;
		anim = nullptr;
	}
	virtual ~Actor() {
		if (anim != nullptr) {
			delete anim;
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
};