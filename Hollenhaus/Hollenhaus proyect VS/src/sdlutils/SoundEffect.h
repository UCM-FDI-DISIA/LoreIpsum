// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <string>
#include <SDL_mixer.h>
#include <cassert>

#define _CHECK_CHANNEL_(channel) \
	assert(channel >= -1 && channel < static_cast<int>(channels_));

class SoundEffect {
public:

	// cannot copy objects of this type!
	SoundEffect& operator=(SoundEffect &other) = delete;
	SoundEffect(const SoundEffect&) = delete;

	SoundEffect(const std::string &fileName) {
		chunk_ = Mix_LoadWAV(fileName.c_str());
		assert(chunk_ != nullptr);
	}

	SoundEffect(SoundEffect &&other) noexcept {
		chunk_ = other.chunk_;
		other.chunk_ = nullptr;
	}

	SoundEffect& operator=(SoundEffect &&other) noexcept {
		this->~SoundEffect();
		chunk_ = other.chunk_;
		other.chunk_ = nullptr;
		return *this;
	}

	virtual ~SoundEffect() {
		if (chunk_ != nullptr)
			Mix_FreeChunk(chunk_);
	}

	inline int play(int loops = 0, int channel = -1) const {
		_CHECK_CHANNEL_(channel);
		assert(loops >= -1);
		return Mix_PlayChannel(channel, chunk_, loops);
	}

	inline int setVolume(int volume) {
		assert(volume >= 0 && volume <= 128);
		return Mix_VolumeChunk(chunk_, volume);
	}

	// static methods for sound effects
	//
	inline static void pauseChannel(int channel = -1) {
		_CHECK_CHANNEL_(channel);
		Mix_Pause(channel);
	}

	inline static void resumeChannel(int channel = -1) {
		_CHECK_CHANNEL_(channel);
		Mix_Resume(channel);
	}

	inline static void haltChannel(int channel = -1) {
		_CHECK_CHANNEL_(channel);
		Mix_HaltChannel(channel);
	}

	inline static int setChannelVolume(int volume, int channel = -1) {
		_CHECK_CHANNEL_(channel);
		assert(volume >= 0 && volume <= 128);
		return Mix_Volume(channel, volume);
	}

	inline static int setNumberofChannels(int n) {
		assert(n > 0);
		return channels_ = Mix_AllocateChannels(n);
	}

private:

	inline static void checkChannel(int channel) {
		assert(channel >= -1 && channel < static_cast<int>(channels_));
	}

	Mix_Chunk *chunk_;
	static int channels_; // initialized in cpp
};

