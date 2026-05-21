#pragma once
#include "Object3D.h"

class Coin : public Object3D {
public:
	Coin(const VECTOR3& pos);
	~Coin();
	void Update() override;
	void CollidePlayer(VECTOR3 pos, float radius);
private:
	enum State {
		sNormal = 0,
		sGot,
	};
	State state;
	float timer; // ‰ñ“]‚ÌŠÔ‚ğ
	VECTOR3 base; // ‰ŠúˆÊ’u
};