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


	Volume(30);
}

void SoundManager::Volume(int i)
{
	Mix_MasterVolume(i);
}

void SoundManager::ChannelVolume(std::string channel, int v)
{
	sdlutils().soundEffects().at(channel).setChannelVolume(v);
}

void SoundManager::startMusic(Musics::MUSIC m)
{
	auto n = music_names[m];
	sdlutils().soundEffects().at(n).play(-1);
}

void SoundManager::stopMusic(Musics::MUSIC m)
{
	auto n = music_names[m];
	sdlutils().soundEffects().at(n).pauseChannel();

}

