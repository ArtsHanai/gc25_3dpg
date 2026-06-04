#include "Pad.h"
Pad::Pad()
{
}

Pad::~Pad()
{
}

void Pad::Update()
{
	GetJoypadXInputState(DX_INPUT_PAD1, &state);
}

void Pad::Draw()
{
	DrawFormatString(0, 100, GetColor(255,255,255), "%d %d", 
							state.ThumbLX, state.ThumbLY);
}

float Pad::GetRStickX()
{
	float val = state.ThumbLX / 32767.0f;
	val = max(val, -1.0f);
	return val;
}
