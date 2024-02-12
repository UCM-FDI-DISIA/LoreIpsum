// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cassert>
#include <ctime>
#include <random>

#include "RandomNumberGenerator.h"

class RandomNumberGenerator {
public:

	RandomNumberGenerator(const RandomNumberGenerator&) = delete;
	RandomNumberGenerator& operator=(RandomNumberGenerator&) = delete;

	RandomNumberGenerator() :
		RandomNumberGenerator(static_cast<unsigned int>(std::time(0))) {
	}

	RandomNumberGenerator(unsigned seed) :
			gen_(seed), dist_() {
	}

	virtual ~RandomNumberGenerator() {
	}

	inline int nextInt() {
		return dist_(gen_);
	}

	// return an integer between low (inclusive) and high (exclusive)
	inline int nextInt(int low, int high) {
		assert(low < high);
		return low + (nextInt() % (high - low));
	}

private:
	std::mt19937 gen_;
	std::uniform_int_distribution<int> dist_;

};

