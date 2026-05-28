#include "ReadyGo.h"
#include "Player.h"
#include "SoundDriver.h"

ReadyGo::ReadyGo()
{
	hReady = LoadGraph("data/images/ready.png");
	hGo = LoadGraph("data/images/go.png");
	timer = 2.0f; // Ready‚Ì•\Ž¦ŽžŠÔi•bj
	SoundDriver::Load("data/tmpSound/go");
}

ReadyGo::~ReadyGo()
{
}

void ReadyGo::Update()
{
	bool t = timer;
	timer -= Time::DeltaTime();
	if (t >= 0.0f && timer < 0.0f) {
		Player* p = FindGameObject<Player>();
		p->AllowMove();
		SoundDriver::Play("go");
	}
	if (timer < -0.5f) {
		DestroyMe();
	}
}

void ReadyGo::Draw()
{
	if (timer >= 0.0f) {
		DrawGraph(0, 0, hReady, TRUE);
	} else {
		DrawGraph(0, 0, hGo, TRUE);
	}
}
