#include "..\pchs\pch.h"
#include "SoundManager.h"
#include "../sdlutils/SoundEffect.h"
#include "../sdlutils/Music.h"
#include <SDL_mixer.h>



SoundManager::SoundManager()
{
	init();
}

SoundManager::~SoundManager()
{
}

void SoundManager::init()
{
	music_names.push_back("deckbuilder_theme");
	music_names.push_back("battletheme_paul");
	music_names.push_back("battletheme_tarot");
	music_names.push_back("shoptheme");
	music_names.push_back("citytheme");
	music_names.push_back("mainmenutheme");

	// INES AQUI CAMBIAR

	master_volume = 70;
	Volume(master_volume);

}

int SoundManager::Volume(int i)
{
	master_volume = i;
	return Mix_MasterVolume(i);
}

void SoundManager::addVolume(int i)
{
	master_volume += i;
	if (master_volume <= 0) master_volume = 0;
	else if (master_volume >= 128) master_volume = 128;
	Mix_MasterVolume(master_volume);

#ifdef _DEBUG
	std::cout << "volume: " << master_volume;
#endif // DEBUG

}

void SoundManager::ChannelVolume(Musics::MUSIC channel, int v)
{
	auto n = music_names[channel];
	sdlutils().soundEffects().at(n).setChannelVolume(v, channel);

}

void SoundManager::startDynamicMusic(Musics::MUSIC a, Musics::MUSIC b)
{
	startMusic(a);
	ChannelVolume(a, master_volume);
	startMusic(b);
	ChannelVolume(b, 0);

	//sdlutils().soundEffects().at(a).
}

void SoundManager::stopDynamicMusic(Musics::MUSIC a, Musics::MUSIC b)
{
	stopMusic(a);
	stopMusic(b);
}

void SoundManager::changeDynamicMusic(Musics::MUSIC a, Musics::MUSIC b)
{
	auto n = music_names[a];
	auto m = music_names[b];

	sdlutils().soundEffects().at(n).setChannelVolume(master_volume, a);
	sdlutils().soundEffects().at(m).setChannelVolume(0, b);
}

void SoundManager::startMusic(Musics::MUSIC m)
{
	auto n = music_names[m];
	sdlutils().soundEffects().at(n).play(-1, m);
}

void SoundManager::stopMusic(Musics::MUSIC m)
{
	auto n = music_names[m];
	sdlutils().soundEffects().at(n).pauseChannel(m);

}

