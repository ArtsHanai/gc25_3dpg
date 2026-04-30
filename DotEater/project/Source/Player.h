#pragma once
// Player.h
#include "Object3D.h"

class Player : public Object3D {
public:
	Player(const VECTOR3& pos);
	~Player();
	void Update() override;
private:
	// アニメーションの実験
	int hAnim; // アニメーションデータのハンドラー
	int attID; // アタッチした番号
	float time;
};