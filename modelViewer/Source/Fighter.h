#pragma once
#include "Object3D.h"

class Fighter : public Object3D
{
public:
	Fighter();
	~Fighter();
	void Update() override;
private:
	VECTOR3 velocity;
};