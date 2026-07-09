#include "Fighter.h"
#include <assert.h>
#include "../ImGui/imgui.h"

Fighter::Fighter()
{
	hModel = MV1LoadModel("data/Fighter.mv1");
	assert(hModel>0);
	transform.position = VECTOR3(0, 0, 0);
	transform.rotation.SetRot(DX_PI_F/2.0f, 0, 0);
	velocity = VECTOR3(0, 0, 1);
}

Fighter::~Fighter()
{
	MV1DeleteModel(hModel);
	hModel = -1;
}

void Fighter::Update()
{
	// Fighterを回す
	// A-D W-S Q-E
	if (CheckHitKey(KEY_INPUT_A)) {
//		transform.rotation.RotY(-3.0f * DegToRad);
		transform.rotation.RotAxis(
					transform.Up(), -3.0f * DegToRad);
	}
	if (CheckHitKey(KEY_INPUT_D)) {
//		transform.rotation.RotY(3.0f * DegToRad);
		transform.rotation.RotAxis(
					transform.Up(), 3.0f * DegToRad);
	}
	if (CheckHitKey(KEY_INPUT_W)) {
//		transform.rotation.RotX(3.0f * DegToRad);
		transform.rotation.RotAxis(
			transform.Right(), 3.0f * DegToRad);
	}
	if (CheckHitKey(KEY_INPUT_S)) {
//		transform.rotation.RotX(-3.0f * DegToRad);
		transform.rotation.RotAxis(
			transform.Right(), -3.0f * DegToRad);
	}
	if (CheckHitKey(KEY_INPUT_Q)) {
//		transform.rotation.RotZ(3.0f * DegToRad);
		transform.rotation.RotAxis(
			transform.Forward(), 3.0f * DegToRad);
	}
	if (CheckHitKey(KEY_INPUT_E)) {
//		transform.rotation.RotZ(-3.0f * DegToRad);
		transform.rotation.RotAxis(
			transform.Forward(), -3.0f * DegToRad);
	}
	// 向いている方に進ませる
//	transform.position += transform.Forward() * 3.0f;

	ImGui::Begin("Fighter");
	VECTOR3 rot = transform.rotation.GetRot();
	int deg = rot.y * RedToDeg;
	ImGui::InputInt("roty", &deg);
	bool f;
	ImGui::Checkbox("F", &f);
	ImGui::End();
}