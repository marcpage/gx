#include "posix/MessageException.h"

template<class T>
inline SmartPtr<T>::SmartPtr(T *p)
	:_p(p) {
	retain();
}
template<class T>
inline SmartPtr<T>::SmartPtr(const SmartPtr<T> &other)
	:_p(other._p) {
	retain();
}
template<class T>
inline SmartPtr<T>::~SmartPtr() {
	release();
}
template<class T>
inline SmartPtr<T> &SmartPtr<T>::operator=(const SmartPtr<T> &other) {
	if(this != &other) {
		release();
		_p= other._p;
		retain();
	}
	return *this;
}
template<class T>
inline T &SmartPtr<T>::operator*() const {
	AssertMessageException(*this);
	return *_p;
}
template<class T>
inline T *SmartPtr<T>::operator->() const {
	AssertMessageException(*this);
	return _p;
}
template<class T>
SmartPtr<T>::operator bool() const {
	return NULL != _p;
}
template<class T>
inline int32_t SmartPtr<T>::retain() const {
	if(*this) {
		return _p->retain();
	}
	return -1;
}
template<class T>
inline void SmartPtr<T>::release() const {
	if(*this) {
		_p->release();
	}
}
template<class T>
inline int32_t SmartPtr<T>::references() const {
	if(*this) {
		return _p->references();
	}
	return -1;
}
