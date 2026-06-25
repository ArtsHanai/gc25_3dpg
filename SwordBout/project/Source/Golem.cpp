#include "Golem.h"

Golem::Golem(VECTOR3 pos, float rotY)
{
hModel = MV1LoadModel("data/models/Character/Golem/Golem.mv1");
transform.position = pos;
transform.rotation.y = rotY;


}

Golem::~Golem()
{
}

void Golem::Update()
{
}
