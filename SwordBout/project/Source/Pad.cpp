#include "Pad.h"

namespace { // 無名namespace このcppからしか見れない
	XINPUT_STATE state;
	XINPUT_STATE prevState; // 1フレーム前のstate
};

Pad::Pad()
{
}

Pad::~Pad()
{
}

void Pad::Update()
{
	prevState = state;
	GetJoypadXInputState(DX_INPUT_PAD1, &state);

	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		state.ThumbRX = 32767;
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		state.ThumbRX = -32768;
	}
	if (CheckHitKey(KEY_INPUT_UP)) {
		state.ThumbRY = 32767;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		state.ThumbRY = -32768;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		state.ThumbLX = 32767;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		state.ThumbLX = -32768;
	}
	if (CheckHitKey(KEY_INPUT_W)) {
		state.ThumbLY = 32767;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		state.ThumbLY = -32768;
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

VECTOR2 Pad::GetLStick()
{
	float x = state.ThumbLX / 32767.0f;
	float y = state.ThumbLY / 32767.0f;
	if (x * x + y * y < 0.2f * 0.2f) { // ベクトルの長さが小さい
		return VECTOR2();
	}
	return VECTOR2(x, y);
}

bool Pad::IsPress(int key)
{
	return state.Buttons[key] != 0;
}

bool Pad::OnPush(int key)
{
	// prevStateでは０で、
	// stateでは１になっていれば押した瞬間：trueを返す
	if (prevState.Buttons[key] == 0) {
		if (state.Buttons[key] != 0) {
			return true;
		}
	}
	return false;
}
