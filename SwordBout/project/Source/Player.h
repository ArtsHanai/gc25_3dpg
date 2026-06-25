#pragma once
#include "Actor.h"
#include "Animator.h"

class Player : public Actor {
public:
	Player(VECTOR3 pos, float rotY);
	~Player();
	void Update() override;
	void Draw() override;
private:
	// 状態のenumを作る
	enum State {
		sNormal, //通常（待機、走り）
		sAttack1, // 攻撃１
		sAttack2, // 攻撃２
		sAttack3, // 攻撃３
		sDamage, // ダメージ
		// 残りは後で
	};
	State state; // 状態を持つ変数
	// 状態ごとのUpdate関数を作る
	void UpdateNormal();
	void UpdateAttack1();
	void UpdateAttack2();
	void UpdateAttack3();
	void UpdateDamage();
	bool attackPushed;
};