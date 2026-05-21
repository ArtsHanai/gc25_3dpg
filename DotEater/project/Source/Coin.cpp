#include "Coin.h"
#include "Player.h"

Coin::Coin(const VECTOR3& pos)
{
	transform.position = pos;
	hModel = MV1LoadModel("data/models/Coin.mv1");
	timer = 0.0f;
	state = State::sNormal;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	if (state == sNormal) {
		timer += Time::DeltaTime();
		if (timer <= 0.5f) { // 0～0.5
			float t = timer / 0.5f;
			float r = easeOutBounce(t);
			transform.rotation.y = Lerp<float>(0, DX_PI, r);
		} else if (timer <= 1.0f) { // 0.5～1.0
			transform.rotation.y = DX_PI;
		} else if (timer <= 1.5f) { // 1.0～1.5
			transform.rotation.y = Lerp<float>(DX_PI, DX_PI * 2,
				(timer - 1.0f) / 0.5f);
		} else { // 1.5～2.0
			transform.rotation.y = DX_PI * 2;
			if (timer >= 2.0f) {
				timer -= 2.0f;
			}
		}
	} else { // 取られた時
		// プレイヤーに近づいていき、プレイヤーに重なったら消える
		Player* pl = FindGameObject<Player>();
		VECTOR3 pPos = pl->GetTransform().position;
		timer += Time::DeltaTime();
		float rate = timer / 0.5f;
		if (rate >= 1.0f) {
			DestroyMe();
		} else {
			transform.position = Lerp<VECTOR3>(base, pPos, rate);
		}
		//VECTOR3 v = pPos - transform.position;
		//if (VSize(v) >= 300.0f * Time::DeltaTime()) {
		//	VECTOR3 vn = VNorm(v);
		//	v = vn * 300.0f * Time::DeltaTime();
		//	transform.position += v;
		//} else {
		//	// ゲージが増える、SE、エフェクト
		//	DestroyMe();
		//}		
	}
}

void Coin::CollidePlayer(VECTOR3 pos, float radius)
{
//	コインの座標　transform.position
//	プレイヤーの座標　pos
//	この距離が半径より短ければstate = State::sGotにする
	if (state == State::sGot) // すでに取られている
		return;

	VECTOR3 dist = transform.position - pos;
	if (VSize(dist) <= radius) {
		state = State::sGot;
		base = transform.position;
		timer = 0.0f;
	}
}
