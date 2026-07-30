#include "Light.h"
#include "../ImGui/imgui.h"

Light::Light()
{
	SetGlobalAmbientLight(GetColorF(0.2f, 0.2f, 0.5f, 0.0));
	SetLightAmbColor(GetColorF(0.2, 0.2, 0.5, 0.));
//	ChangeLightTypePoint(VECTOR3(0,200,0), 2000,0,0.0006,0);
	ChangeLightTypeDir(VECTOR3(-0.7, -0.7, 0));
	SetLightDifColor(GetColorF(0.8,0.0,0.0, 0.0));
	SetLightSpcColor(GetColorF(0.8, 0.0, 0.0, 0.0));
	SetFogEnable(TRUE);
	SetFogColor(255,255,0);
	SetFogStartEnd(100.0f, 10000.f);
}

Light::~Light()
{
}
float r, g, b;

void Light::Update()
{
	ImGui::Begin("Color");
	ImGui::SliderFloat("R", &r, 0.0f, 1.0f);
	ImGui::SliderFloat("G", &g, 0.0f, 1.0f);
	ImGui::SliderFloat("B", &b, 0.0f, 1.0f);
	ImGui::End();
	SetLightDifColor(GetColorF(r, g, b, 0.0));
	SetLightSpcColor(GetColorF(r, g, b, 0.0));
}

void Light::Draw()
{
}
