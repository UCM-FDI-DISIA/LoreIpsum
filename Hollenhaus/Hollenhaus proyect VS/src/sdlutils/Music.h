// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <string>
#include <SDL_mixer.h>

class Music
{
public:
	// cannot copy objects of this type!
	Music& operator=(Music& other) = delete;
	Music(const Music&) = delete;

	Music(const std::string& fileName)
	{
		music_ = Mix_LoadMUS(fileName.c_str());
		assert(music_ != nullptr);
	}

	Music(Music&& other) noexcept
	{
		music_ = other.music_;
		other.music_ = nullptr;
	}

	Music& operator=(Music&& other) noexcept
	{
		this->~Music();
		music_ = other.music_;
		other.music_ = nullptr;
		return *this;
	}

	virtual ~Music()
	{
		if (music_ != nullptr)
			Mix_FreeMusic(music_);
	}

	void play(int loops = -1) const
	{
		assert(loops >= -1 && music_ != nullptr);
		Mix_PlayMusic(music_, loops);
	}

	static int setMusicVolume(int volume)
	{
		assert(volume >= 0 && volume <= 128);
		return Mix_VolumeMusic(volume);
	}

	static void haltMusic()
	{
		Mix_HaltMusic();
	}

	static void pauseMusic()
	{
		Mix_PauseMusic();
	}

	static void resumeMusic()
	{
		Mix_ResumeMusic();
	}

private:
	Mix_Music* music_;
};
