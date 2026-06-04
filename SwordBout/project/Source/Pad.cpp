#include "Pad.h"

namespace { // –³–¼namespace ‚±‚Ìcpp‚©‚ç‚µ‚©Œ©‚ê‚È‚¢
	XINPUT_STATE state;
};

Pad::Pad()
{
}

Pad::~Pad()
{
}

void Pad::Update()
{
	GetJoypadXInputState(DX_INPUT_PAD1, &state);
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		state.ThumbRX = 32767;
		if (CheckHitKey(KEY_INPUT_RSHIFT)) {
			state.ThumbRX /= 2;
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		state.ThumbRX = -32768;
	}
}

void Pad::Draw()
{
	DrawFormatString(0, 100, GetColor(255,255,255), "%d %d", 
							state.ThumbLX, state.ThumbLY);
}

float StickValue(int v)
{
	float val = v / 32767.0f;
	val = max(val, -1.0f);
	if (val > -0.2f && val < 0.2f) {
		val = 0.0f;
	}
	return val;
}

float Pad::GetRStickX()
{
	return StickValue(state.ThumbRX);
}

float Pad::GetRStickY()
{
	return StickValue(state.ThumbRY);
}

float Pad::GetLStickX()
{
	return StickValue(state.ThumbLX);
}

float Pad::GetLStickY()
{
	return StickValue(state.ThumbLY);
}
