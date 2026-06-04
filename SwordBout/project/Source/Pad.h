#pragma once
#include "../Library/GameObject.h"

class Pad : public GameObject {
public:
	Pad();
	~Pad();
	void Update() override;
	void Draw() override;
	float GetRStickX(); // -1.0Å`+1.0Çï‘Ç∑
private:
	XINPUT_STATE state;
};