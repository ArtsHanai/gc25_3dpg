#pragma once
#include "IEnemy.h"
#include "Animator.h"

class Golem : public IEnemy {
public:
	Golem(VECTOR3 pos, float rotY);
	~Golem();
	void Update() override;
	//	void Draw() override;
};