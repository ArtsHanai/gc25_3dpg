#pragma once
#include "Object3D.h"

class Player : public Object3D {
public:
	Player(VECTOR3 pos, float rotY);
	~Player();
	void Update() override;
};