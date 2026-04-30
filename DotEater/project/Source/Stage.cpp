#include "Stage.h"
#include <vector>
#include "csvReader.h"
#include "Player.h"

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
