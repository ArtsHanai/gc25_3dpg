#pragma once
// Object3D.h
#include "../Library/GameObject.h"

class Transform {
public:
	VECTOR3 position;
	VECTOR3 rotation;
	VECTOR3 scale;
	Transform() { scale = VECTOR3(1, 1, 1); }
	MATRIX RotMatrix() const
	{
		MATRIX mRotX = MGetRotX(rotation.x);
		MATRIX mRotY = MGetRotY(rotation.y);
		MATRIX mRotZ = MGetRotZ(rotation.z);
		return mRotZ * mRotX * mRotY;
	}
	VECTOR3 Forward() const
	{
		return VECTOR3(0, 0, 1) * RotMatrix();
	}
	VECTOR3 Right()
	{
		return VECTOR3(1, 0, 0) * RotMatrix();
	}
	VECTOR3 Up()
	{
		return VECTOR3(0, 1, 0) * RotMatrix();
	}
};

class Object3D : public GameObject
{
public:
	Object3D();
	virtual ~Object3D();
	virtual void Draw() override;
	const Transform& GetTransform() { return transform; }
protected:
	int hModel;
	Transform transform;
};