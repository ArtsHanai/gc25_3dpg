#include "TitleScene.h"
#include "Input.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	DrawFormatString(200, 10, GetColor(255,255,255),
		"%f", Time::DeltaTime());

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
