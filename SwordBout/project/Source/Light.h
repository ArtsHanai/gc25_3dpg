#pragma once
//Light.h
#include "Object3D.h"

class Light : public Object3D
{
public:
	Light();
	~Light();
	void Update() override;
	void Draw() override;
	void MakeFlash(unsigned int color, VECTOR3 pos, float time); 
};