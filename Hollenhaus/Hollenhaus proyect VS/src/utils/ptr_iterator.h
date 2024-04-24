// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

template<typename T>
struct ptr_iterator {
	T *ptr_;
	ptr_iterator(T *ptr) {
		ptr_ = ptr;
	}

	T& operator*() {
		return *ptr_;
	}

	ptr_iterator& operator++() {
		ptr_++;
		return *this;
	}

	ptr_iterator operator++(int) {
		auto tmp = *this;
		++(*this);
		return tmp;
	}

	bool operator==(ptr_iterator &o) {
		return ptr_ == o.ptr_;
	}

	bool operator!=(ptr_iterator &o) {
		return ptr_ != o.ptr_;
	}

};

