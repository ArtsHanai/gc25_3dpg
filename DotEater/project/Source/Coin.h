#pragma once
#include "Object3D.h"

class Coin : public Object3D {
public:
	Coin(const VECTOR3& pos);
	~Coin();
	void Update() override;
private:
	float timer; // ‰ñ“]‚ÌŽžŠÔ‚ð
};