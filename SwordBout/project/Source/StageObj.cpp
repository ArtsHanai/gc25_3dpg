#include "StageObj.h"
#include "Actor.h"

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
	MATRIX mRotX = MGetRotX(transform.rotation.x);
	MATRIX mRotY = MGetRotY(transform.rotation.y);
	MATRIX mRotZ = MGetRotZ(transform.rotation.z);
	MATRIX mTrans = MGetTranslate(transform.position);
	MATRIX m = mRotZ * mRotX * mRotY * mTrans;
	MV1SetMatrix(hHitModel, m);
	MV1SetupCollInfo(hHitModel);
	MV1RefreshCollInfo(hHitModel);
}

StageObj::~StageObj()
{
	MV1DeleteModel(hModel);
	hModel = -1;
}

void StageObj::Draw()
{
	if (CheckHitKey(KEY_INPUT_O)) {
		MATRIX mRotX = MGetRotX(transform.rotation.x);
		MATRIX mRotY = MGetRotY(transform.rotation.y);
		MATRIX mRotZ = MGetRotZ(transform.rotation.z);
		MATRIX mTrans = MGetTranslate(transform.position);
		MATRIX m = mRotZ * mRotX * mRotY * mTrans;
		MV1SetMatrix(hHitModel, m);
		MV1DrawModel(hHitModel);
	} else {
		Object3D::Draw();
	}
}

VECTOR3 StageObj::CollideCapsule(const VECTOR3& base, CapsuleCollider* cap)
{
	VECTOR3 ret = VECTOR3(0, 0, 0);
	float maxVal = 0; // Å‰‚Í‚O

	//“–‚½‚è”»’è
	MV1_COLL_RESULT_POLY_DIM result =
		MV1CollCheck_Capsule(hHitModel, -1, cap->pos1 + base, cap->pos2 + base, cap->rad);

	for (int i = 0; i < result.HitNum; i++) {

		if (result.Dim[i].Normal.y >= cosf(30.0f * DegToRad)) {
			continue;
		}
		float len = Segment_Triangle_MinLength(cap->pos1 + base,
			cap->pos2 + base, result.Dim[i].Position[0], result.Dim[i].Position[1], result.Dim[i].Position[2]);

		VECTOR3 v = (VECTOR3)(result.Dim[i].Normal) * (cap->rad - len);
		v.y = 0;
		if (VSize(v) > maxVal) {
			maxVal = VSize(v);
			ret = v;
		}
	}
	MV1CollResultPolyDimTerminate(result);
	return ret;
}
