#pragma once
#include "Object3D.h"

class CapsuleCollider;

class Stage : public Object3D {
public:
	Stage();
	~Stage();
	void Update() override;
	bool FindGround(VECTOR3 high, VECTOR3 low, VECTOR3* hit);
	VECTOR3 CollideCapsule(const VECTOR3& base, CapsuleCollider* cap);

private:
	// Stage.dat‚ð“Ç‚ñ‚Å”z’u‚·‚é
	void ParamRead(int st);
};