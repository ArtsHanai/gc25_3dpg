#include "TitleScene.h"
#include "Input.h"
#include <fstream>

using namespace std;
TitleScene::TitleScene()
{
	// ファイルの読み書きテスト
	ofstream ofs("test.txt", ios::binary);
//	ofs << "HANAI" << endl;

	char s[] = "HANAI\n";
	ofs.write(s, 7);

	ofs.write("HANAI", 4);
	ofs.close();

	ifstream ifs("test.txt", ios::binary);
	char t[20];
	ifs.read(t, 20);

//	string s;
//	getline(ifs, s);

	ifs.close();

	// バイナリの場合
	ofstream ob("test.bin", ios::binary);
	struct STR {
		int i;
		float f;
		char m;
		char c;
	};
	STR str;
	str.i = 100;
	str.m = 5;
	str.f = 1.0f;
	str.c = 3;
	ob.write((char*)&str, sizeof(str));
	ob.close();

	// 読む
	STR str2;
	ifstream ib("test.bin", ios::binary);
	ib.read((char*)&str2, sizeof(str2));
	ib.close();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (Input::IsKeyOnTrig(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (Input::IsKeyOnTrig(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DrawString(0, 0, "TITLE SCENE", GetColor(255, 255, 255));
	DrawFormatString(0, 75, GetColor(255, 255, 255), "DxLib: %s", DXLIB_VERSION_STR_T );
	DrawFormatString(0, 100, GetColor(255, 255, 255), "FPS: %4.1f", 1.0f / Time::DeltaTime());
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
