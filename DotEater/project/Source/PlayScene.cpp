#include "PlayScene.h"
#include "../Library/GameObject.h"
#include "Input.h"
#include "Stage.h"
#include "Axis.h"

PlayScene::PlayScene()
{
	SetCameraPositionAndTarget_UpVecY(
		VECTOR3(0,1000, -100), VECTOR3(0, 0, 0));
	new Stage();
	new Axis();
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
