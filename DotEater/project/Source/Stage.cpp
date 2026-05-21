#include "Stage.h"
#include <vector>
#include "csvReader.h"
#include "Player.h"
#include "Coin.h"

using namespace std;

//int map[] = { 1,1,0,1,1,1 };
//int size = sizeof(map)/sizeof(map[0]);
//std::vector<std::vector<int>> map = {
//	{ 1,1,1,1,1,1 },
//	{ 1,0,0,0,1,1 },
//	{ 1,0,1,0,0,1 },
//	{ 1,1,1,1,1,1 },
//};
std::vector<std::vector<int>> map;

Stage::Stage()
{
	hModel = MV1LoadModel(
		"data/models/RedBrickBlock.mv1");
	MV1SetupCollInfo(hModel);

	CsvReader* csv = new CsvReader("data/Stage01.csv");
	for (int z = 0; z < csv->GetLines(); z++) {
		std::vector<int> line;
		for (int x = 0; x < csv->GetColumns(z); x++) {
			int chip = csv->GetInt(z, x);
			line.push_back(chip);
		}
		map.push_back(line);
	}
	delete csv;

	// mapデータの中を見て、３であればnew Player()
	for (int z = 0; z < map.size(); z++) {
		for (int x = 0; x < map[z].size(); x++) {
			if (map[z][x] == 3) {
				new Player(VECTOR3(x * 100, 0, z * -100));
			}
			if (map[z][x] == 2) {
				new Coin(VECTOR3(x * 100, 50, z * -100));
			}
		}
	}
}

Stage::~Stage()
{
}

void Stage::Draw()
{
	for (int z = 0; z < map.size(); z++) {
		for (int x = 0; x < map[z].size(); x++) {
			if (map[z][x] == 1) {
				MV1SetPosition(hModel, VECTOR3(x * 100, 0, z * -100));
				MV1DrawModel(hModel);
			}
		}
	}
}

VECTOR3 Stage::CollideSphere(VECTOR3 center, float rad)
{
	float minVal = rad; // 一番小さい値
	VECTOR3 ret; // リターンする値
	for (int z = 0; z < map.size(); z++) {
		for (int x = 0; x < map[z].size(); x++) {
			if (map[z][x] == 1) {
				MV1SetPosition(hModel, VECTOR3(x * 100, 0, z * -100));
				MV1RefreshCollInfo(hModel);
				MV1_COLL_RESULT_POLY_DIM result =
					MV1CollCheck_Sphere(hModel, -1, center, rad);
				for (int i = 0; i < result.HitNum; i++) {
					VECTOR3 hitPos = result.Dim[i].HitPosition;
					VECTOR3 v = center - hitPos;
					if (VSize(v) < minVal) {
						minVal = VSize(v);
						v.y = 0; // Yの差は見ないようにする
						VECTOR3 v1 = VNorm(v); // 押し出す向き（長さ１）
						float len = rad - VSize(v); // 押し出す長さ
						ret = v1 * len;
					}
				}
			}
		}
	}
	return ret;
}
