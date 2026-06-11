#pragma once
#include "../Library/GameObject.h"
#if false
class Pad : public GameObject {
public:
	Pad();
	~Pad();
	void Update() override;
	void Draw() override;
	float GetRStickX(); // -1.0`+1.0‚ğ•Ô‚·
	float GetRStickY(); // -1.0`+1.0‚ğ•Ô‚·
	float GetLStickX(); // -1.0`+1.0‚ğ•Ô‚·
	float GetLStickY(); // -1.0`+1.0‚ğ•Ô‚·
private:
	XINPUT_STATE state;
};
#endif
// ‚Ç‚±‚©‚ç‚Å‚àŒÄ‚×‚é‡@namespace
#if false
namespace Pad {
	// ƒRƒ“ƒXƒgƒ‰ƒNƒ^[AƒfƒXƒgƒ‰ƒNƒ^[‚Íì‚ê‚È‚¢
	void Update();
	void Draw();
	float GetRStickX(); // -1.0`+1.0‚ğ•Ô‚·
	float GetRStickY(); // -1.0`+1.0‚ğ•Ô‚·
	float GetLStickX(); // -1.0`+1.0‚ğ•Ô‚·
	float GetLStickY(); // -1.0`+1.0‚ğ•Ô‚·
	// ƒƒ“ƒo[•Ï”‚ğ‚Ät‚È‚¢
};
#endif
// staticŠÖ”
#if true
class Pad : public GameObject {
public:
	Pad();
	~Pad();
	void Update();
	void Draw();
	static float GetRStickX(); // -1.0`+1.0‚ğ•Ô‚·
	static float GetRStickY(); // -1.0`+1.0‚ğ•Ô‚·
	static float GetLStickX(); // -1.0`+1.0‚ğ•Ô‚·
	static float GetLStickY(); // -1.0`+1.0‚ğ•Ô‚·
	static VECTOR2 GetLStick();
	static bool IsPress(int key); // ‰Ÿ‚µ‚Ä‚¢‚é‚©
	static bool OnPush(int key); // ‰Ÿ‚µ‚½uŠÔ

	static const int ATTACK = XINPUT_BUTTON_A;
private:
};
#endif
// ƒVƒ“ƒOƒ‹ƒgƒ“i—Bˆêâ‘Î‚É‘¶İ‚·‚éƒCƒ“ƒXƒ^ƒ“ƒXj
#if false
class Pad : public GameObject {
public:
	static Pad* GetInstance() {
		static Pad* inst = nullptr;
		if (inst == nullptr) {
			inst = new Pad();
		}
		return inst;
	}
private:
	Pad();
	~Pad();
public:
	void Update();
	void Draw();
	float GetRStickX(); // -1.0`+1.0‚ğ•Ô‚·
	float GetRStickY(); // -1.0`+1.0‚ğ•Ô‚·
	float GetLStickX(); // -1.0`+1.0‚ğ•Ô‚·
	float GetLStickY(); // -1.0`+1.0‚ğ•Ô‚·
private:
	XINPUT_STATE state;
};
#endif