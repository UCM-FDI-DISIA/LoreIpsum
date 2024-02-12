// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <cassert>

class VirtualTimer {
public:
	VirtualTimer() {
		reset();
	}

	virtual ~VirtualTimer() {
	}

	inline void reset() {
		zeroTime_ = SDL_GetTicks();
		paused_ = false;
	}

	inline Uint32 currTime() const {
		return paused_ ?
				pauseStartRealTime_ - zeroTime_ : SDL_GetTicks() - zeroTime_;
	}

	inline void pause() {
		if (!paused_) {
			paused_ = true;
			pauseStartRealTime_ = SDL_GetTicks();
		}
	}

	inline void resume() {
		if (paused_) {
			zeroTime_ += (SDL_GetTicks() - pauseStartRealTime_);
			paused_ = false;
		}
	}

private:
	bool paused_;
	Uint32 zeroTime_;
	Uint32 pauseStartRealTime_;
};

