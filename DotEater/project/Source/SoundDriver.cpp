#include "SoundDriver.h"
#include <unordered_map>
#include "myDxLib.h"

static const std::string folder = "data/sounds/";
static const std::string expr = ".mp3";

std::unordered_map<std::string, int> sounds;
// int sounds[std::string]という型

void SoundDriver::Load(std::string filename) {
	if (sounds[filename] > 0)
		return;
	std::string f = filename;
	if (filename.substr(0, 5) != "data/") { // フォルダ指定がない
		f = folder+f;
	}
	if (filename.find('.') == std::string::npos) { // 拡張子がない
		f = f + expr;
	}
	int h = LoadSoundMem(f.c_str());
	if (h > 0) {
		sounds[filename] = h;
	}
}

void SoundDriver::Play(std::string filename) {
	int h = sounds[filename];
	if (h > 0) {
		PlaySoundMem(h, DX_PLAYTYPE_BACK);
	}
}
