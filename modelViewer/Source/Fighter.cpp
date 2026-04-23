#include "Fighter.h"
#include <assert.h>
#include "../ImGui/imgui.h"

Fighter::Fighter()
{
	hModel = MV1LoadModel("data/Fighter.mv1");
	assert(hModel>0);
	transform.position = VECTOR3(0, 0, 0);
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
		transform.rotation.y -= 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		transform.rotation.y += 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_W)) {
		transform.rotation.x += 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		transform.rotation.x -= 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_Q)) {
		transform.rotation.z += 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_E)) {
		transform.rotation.z -= 3.0f * DegToRad;
	}
	// 向いている方に進ませる
	transform.position += transform.Forward() * 3.0f;

	ImGui::Begin("Fighter");
	int deg = transform.rotation.y * RedToDeg;
	ImGui::InputInt("roty", &deg);
	bool f;
	ImGui::Checkbox("F", &f);
	ImGui::End();
}