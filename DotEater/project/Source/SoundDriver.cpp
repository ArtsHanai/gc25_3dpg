#include "SoundDriver.h"
#include <unordered_map>
#include "myDxLib.h"

std::unordered_map<std::string, int> sounds;
// int sounds[std::string]‚Æ‚¢‚¤Œ^

void SoundDriver::Load(std::string filename) {
	if (sounds[filename] > 0)
		return;

	int h = LoadSoundMem(filename.c_str());
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
