#include "PlayScene.h"
#include "../Library/GameObject.h"
#include "Input.h"
#include "Player.h"
#include "Stage.h"
#include "Camera.h"
#include "Pad.h"
#include "Goblin.h"
#include "Golem.h"

PlayScene::PlayScene()
{
	new Player(VECTOR3(0,0,0), 0);
	new Stage();
	new Camera();
	new Pad();
	new Goblin(VECTOR3(0, 100, 300), 0);
	new Goblin(VECTOR3(-200, 100, 300), 0);
	new Golem(VECTOR3(200, 0, 300), 0);
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
