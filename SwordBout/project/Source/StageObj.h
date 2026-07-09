#pragma once
#include "Object3D.h"

class StageObj : public Object3D {
public:
	StageObj(int id, const VECTOR3& position, VECTOR3 rotation, VECTOR3 scale);
	~StageObj();
};