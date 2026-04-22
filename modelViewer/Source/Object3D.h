#pragma once
// Object3D.h
#include "../Library/GameObject.h"

class Transform {
public:
	VECTOR3 position;
	VECTOR3 rotation;
	VECTOR3 scale;
	Transform() { scale = VECTOR3(1, 1, 1); }
};

class Object3D : public GameObject
{
public:
	Object3D();
	virtual ~Object3D();
	virtual void Draw() override;
protected:
	int hModel;
	Transform transform;
};