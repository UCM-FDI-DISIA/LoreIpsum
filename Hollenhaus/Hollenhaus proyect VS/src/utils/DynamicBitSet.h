// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cassert>
#include <cstdint>
#include <ctime>
#include <iostream>

using namespace std;

class DynamicBitSet {
	using blockType = uint8_t;
	static const std::size_t bitsPerBlock = (sizeof(blockType) * 8);
public:

	class BlockRef {
	public:
		BlockRef(BlockRef&& o) {
			block_ = o.block_;
			mask_ = o.mask_;
		}
		BlockRef(const BlockRef& o) {
			block_ = o.block_;
			mask_ = o.mask_;
		}

		BlockRef(blockType *block, blockType mask) {
			block_ = block;
			mask_ = mask;
		}

		BlockRef& operator=(const bool v) {
			if (v) {
				*block_ = *block_ | mask_;
			} else {
				*block_ = *block_ & ~mask_;
			}
			return *this;
		}

		operator bool() {
			return (*block_ & mask_) > 0;
		}


	private:
		blockType mask_;
		blockType *block_;
	};


	DynamicBitSet(std::size_t size) {
		size_ = size;
		bits_ = new blockType[size_ / bitsPerBlock + 1]();
	}

	virtual ~DynamicBitSet() {
		delete[] bits_;
	}

	bool isSet(std::size_t n) {
		assert(n < size_);
		std::size_t blockIdx = n / bitsPerBlock;
		blockType mask = 1 << (n % bitsPerBlock);
		return (bits_[blockIdx] & mask) > 0;
	}

	void set(std::size_t n, bool v) {
		assert(n < size_);
		std::size_t blockIdx = n / bitsPerBlock;
		blockType mask = 1 << (n % bitsPerBlock);
		if (v) {
			bits_[blockIdx] = bits_[blockIdx] | mask;
		} else {
			bits_[blockIdx] = bits_[blockIdx] & ~mask;
		}
	}

	BlockRef operator[](std::size_t n) {
		BlockRef x(&bits_[n / bitsPerBlock], 1 << (n % bitsPerBlock));
		return x;
	}

private:
	std::size_t size_;
	blockType *bits_;
};

