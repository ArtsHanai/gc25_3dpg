#pragma once
// Object3D.h
#include "../Library/GameObject.h"

class Rotation {
public:
	Rotation();
	~Rotation();
	void SetRot(float x, float y, float z);
	VECTOR3 GetRot();
	void RotX(float x);
	void RotY(float y);
	void RotZ(float z);
	void RotAxis(VECTOR3 axis, float r);
	MATRIX Matrix() const { return rot; }
private:
	MATRIX rot;
};

class Transform {
public:
	VECTOR3 position;
	Rotation rotation;
	VECTOR3 scale;
	Transform() { scale = VECTOR3(1, 1, 1); }
	VECTOR3 Forward()
	{
		return VECTOR3(0, 0, 1) * rotation.Matrix();
	}
	VECTOR3 Right()
	{
		return VECTOR3(1, 0, 0) * rotation.Matrix();
	}
	VECTOR3 Up()
	{
		return VECTOR3(0, 1, 0) * rotation.Matrix();
	}
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