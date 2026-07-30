#pragma once
#include "Object3D.h"

class CapsuleCollider;

class StageObj : public Object3D {
public:
	StageObj(int id, const VECTOR3& position, VECTOR3 rotation, VECTOR3 scale);
	~StageObj();
	void Draw() override;
	VECTOR3 CollideCapsule(const VECTOR3& base, CapsuleCollider* cap);
private:
	int hHitModel;
};