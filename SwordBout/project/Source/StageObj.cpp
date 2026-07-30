#include "StageObj.h"

StageObj::StageObj(int id, const VECTOR3& position, VECTOR3 rotation, VECTOR3 scale)
{
	char fname[40];
	sprintf_s<40>(fname, "data/models/Stage/Stage_Obj%03d.mv1", id);
	hModel = MV1LoadModel(fname);

	sprintf_s<40>(fname, "data/models/Stage/Stage_Obj%03d_c.mv1", id);
	hHitModel = MV1LoadModel(fname);

	transform.position = position;
	transform.rotation = rotation;
	transform.scale = scale;
}

StageObj::~StageObj()
{
	MV1DeleteModel(hModel);
	hModel = -1;
}

void StageObj::Draw()
{
}
