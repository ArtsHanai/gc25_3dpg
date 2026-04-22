#include "Fighter.h"
#include <assert.h>

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
	transform.position += velocity / 2.0f;
}