#include "Axis.h"

Axis::Axis()
{
}

Axis::~Axis()
{
}

void Axis::Draw()
{
	DrawLine3D(VECTOR3(-100, 0, 0), VECTOR3(100, 0, 0), C_RED);
	DrawLine3D(VECTOR3(0, -100, 0), VECTOR3(0, 100, 0), C_BLUE);
	DrawLine3D(VECTOR3(0, 0, -100), VECTOR3(0, 0, 100), C_GREEN);
}
