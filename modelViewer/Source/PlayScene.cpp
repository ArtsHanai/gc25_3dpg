#include "PlayScene.h"
#include "../Library/GameObject.h"
#include "Input.h"
#include "Fighter.h"

PlayScene::PlayScene()
{
	SetCameraPositionAndTarget_UpVecY(VGet(0,0,-300), VGet(0,0,0));
	new Fighter();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (Input::IsKeyOnTrig(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
