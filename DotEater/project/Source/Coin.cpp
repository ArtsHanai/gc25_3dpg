#include "Coin.h"

Coin::Coin(const VECTOR3& pos)
{
	transform.position = pos;
	hModel = MV1LoadModel("data/models/Coin.mv1");
	timer = 0.0f;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	timer += Time::DeltaTime();
	if (timer <= 0.5f) { // 0`0.5
		transform.rotation.y = Lerp<float>(0, DX_PI, timer/0.5f);
	} else if (timer <= 1.0f) { // 0.5`1.0
		transform.rotation.y = DX_PI;
	} else if (timer <= 1.5f) { // 1.0`1.5
		transform.rotation.y = Lerp<float>(DX_PI, DX_PI*2,
				(timer-1.0f)/0.5f);
	} else { // 1.5`2.0
		transform.rotation.y = DX_PI*2;
		if (timer >= 2.0f) {
			timer -= 2.0f;
		}
	}
}
