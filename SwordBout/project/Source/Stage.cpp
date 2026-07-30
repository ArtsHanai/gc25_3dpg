#include "Stage.h"
#include "Player.h"
#include "Goblin.h"
#include "Golem.h"
#include "StageObj.h"
#include <fstream>
#include <assert.h>

Stage::Stage()
{
	int stage = 0;
	char fname[40];
	sprintf_s<40>(fname, "data/models/Stage/Stage%02d.mv1", stage);
	hModel = MV1LoadModel(fname);
	MV1SetupCollInfo(hModel);

	ParamRead(stage);
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

VECTOR3 Stage::CollideCapsule(const VECTOR3& base, CapsuleCollider* cap)
{
	VECTOR3 ret = VECTOR3(0,0,0);
	float maxVal = 0; // 最初は０

	//当たり判定
	MV1_COLL_RESULT_POLY_DIM result =
		MV1CollCheck_Capsule(hModel, -1, cap->pos1+base, cap->pos2+base, cap->rad);

	for (int i = 0; i < result.HitNum; i++) {

		if (result.Dim[i].Normal.y >= cosf(30.0f * DegToRad)) {
			continue;
		}
		float len = Segment_Triangle_MinLength(cap->pos1+base,
			cap->pos2+base, result.Dim[i].Position[0], result.Dim[i].Position[1], result.Dim[i].Position[2]);

		VECTOR3 v = (VECTOR3)(result.Dim[i].Normal) * (cap->rad - len);
		v.y = 0;
		if (VSize(v) > maxVal) {
			maxVal = VSize(v);
			ret = v;
		}
 	}
	MV1CollResultPolyDimTerminate(result);

	// 全部のStageObjと当たり判定をして、一番長いものをretに入れる
	std::list<StageObj*> objs = FindGameObjects<StageObj>();
	for (StageObj* ob : objs) {
		VECTOR v = ob->CollideCapsule(base, cap);
		if (VSize(v) > maxVal) {
			maxVal = VSize(v);
			ret = v;
		}
	}
	return ret;
}

void Stage::ParamRead(int st)
{
	struct Header {
		char chunk[4]; // "MAPD"
		int CharaInfoNum; // キャラデータの数
		int ObjectInfoNum; // オブジェクトデータの数
		int EventInfoNum; // イベントデータの数
		VECTOR PlayerPosition; // プレイヤー座標
		float PlayerAngle; // プレイヤーのY軸回転
		int RenderType; // レンダリング方法
		int ClearCondition; // クリア条件
		int killCharaNum; // 倒すべき敵の数
		int killTargetChara; // 倒すべき敵の番号
	};
	struct CharaInfo {
		int id; // 種類(1:Goblin, 2:Bee, 3:Golem, 4:RedGoblin
		VECTOR position; // 座標
		float angle; // Y軸回転
	};
	struct ObjectInfo {
		int id; // 種類
		VECTOR position; // 座標
		VECTOR rotation; // 回転
		VECTOR scale; // 拡縮
	};
	struct EventInfo {
		int type; // 種類
		VECTOR position; // 中心座標
		VECTOR area; // 範囲
		int bgm; // 曲番号
		int objectNum; // オブジェクトの数
		int object[8]; // オブジェクトの番号
	};
	char fname[40];
	sprintf_s<40>(fname, "data/models/Stage/Stage%02d.dat", st);
	std::ifstream ifs(fname, std::ios::binary);
	assert(ifs);
	Header header;
	ifs.read((char*)&header, sizeof(header));
	assert(strncmp(header.chunk, "MAPD", 4) == 0);
	new Player(header.PlayerPosition, header.PlayerAngle);
	for (int i = 0; i < header.CharaInfoNum; i++) {
		CharaInfo chr;
		ifs.read((char*)&chr, sizeof(chr));
		switch (chr.id) {
		case 1:
		case 2:
		case 3:
		case 4:
			new Goblin(chr.position, chr.angle);
			break;
		default:
			assert(false);
			break;
		}
	}
	// ObjectInfoを読んで、StageObjを作る
	for (int i = 0; i < header.ObjectInfoNum; i++) {
		ObjectInfo obj;
		ifs.read((char*)&obj, sizeof(obj));
		new StageObj(obj.id, obj.position, obj.rotation, obj.scale);
	}
	ifs.close();
}