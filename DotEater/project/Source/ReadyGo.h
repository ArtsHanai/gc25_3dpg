#pragma once
//ReadyGo.h
#include "../Library/GameObject.h"

class ReadyGo : public GameObject {
public:
	ReadyGo();
	~ReadyGo();
	void Update() override;
	void Draw() override;
private:
	int hReady;
	int hGo;
	float timer; // カウントダウン用
};