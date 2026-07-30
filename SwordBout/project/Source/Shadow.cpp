#include "Shadow.h"
#include "myDxLib.h"

Shadow::Shadow()
{
	map = MakeShadowMap(4096, 4096);
}

Shadow::~Shadow()
{
}

void Shadow::Make()
{
	SetShadowMapLightDirection(map, VECTOR3(-0.7, -0.7,0));
	SetShadowMapDrawArea(map, VECTOR3(-1000, -1000, -100),
		VECTOR3(1000, 1000, 1000));
	ShadowMap_DrawSetup(map);
}

void Shadow::Use()
{
	ShadowMap_DrawEnd();
	SetUseShadowMap(0, map);
}

void Shadow::End()
{
	SetUseShadowMap(0, -1);
}
