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


	master_volume = 70;
	Volume(master_volume);

}

int SoundManager::Volume(int i)
{
	master_volume = i;
	return Mix_MasterVolume(i);
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

