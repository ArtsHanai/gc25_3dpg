#include "Stage.h"

Stage::Stage()
{
	hModel = MV1LoadModel("data/models/Stage/Stage00.mv1");
	MV1SetupCollInfo(hModel);
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

bool Stage::FindGround(VECTOR3 high, VECTOR3 low, VECTOR3* hit)
{
	MV1_COLL_RESULT_POLY ret = MV1CollCheck_Line(hModel, -1, high, low);
	if (ret.HitFlag) {
		*hit = ret.HitPosition;
		return true;
	}
	return false;
}
