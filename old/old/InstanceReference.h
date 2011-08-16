#ifndef __InstanceReference_h__
#define __InstanceReference_h__

#include "posix/MessageException.h"

template<typename InstanceType>
class InstanceReference {
	public:
		typedef int32_t	DispatchTableIndex;
		enum RetainAction {
			Retain,
			DoNotRetain
		};
		InstanceReference(InstanceType *ptr= NULL, DispatchTableIndex index= 0, RetainAction action=Retain);
		InstanceReference(const InstanceReference &other);
		~InstanceReference();
		InstanceType *operator->();
		const InstanceType *operator->() const;
		InstanceReference &assign(InstanceType *ptr, DispatchTableIndex index= 0, RetainAction action=Retain);
		InstanceReference &operator=(const InstanceReference &other);
		operator bool() const;
		bool valid() const;
		DispatchTableIndex dispatchTable() const;
		void dispatchTable(DispatchTableIndex index);
	private:
		InstanceType		*_ptr;
		DispatchTableIndex	_index;
		void _retain();
		void _release();
};

/** 
	@todo need to have safe typecast
*/
template<typename T1, typename T2>
InstanceReference<T2> &typecastFast(const InstanceReference<T1> &i1, InstanceReference<T2> &i2);

template<typename T1, typename T2>
InstanceReference<T2> &typecastFast(const InstanceReference<T1> &i1, InstanceReference<T2> &i2) {
	i2.assign(const_cast<InstanceReference<T1>*>(&i1)->operator->(), i1.dispatchTable());
}

template<typename InstanceType>
InstanceReference<InstanceType>::InstanceReference(InstanceType *ptr, DispatchTableIndex index, RetainAction action)
	:_ptr(ptr), _index(index) {
	if(Retain == action) {
		_retain();
	}
}
template<typename InstanceType>
InstanceReference<InstanceType>::InstanceReference(const InstanceReference<InstanceType>::InstanceReference &other)
	:_ptr(other._ptr), _index(other._index) {
	_retain();
}
template<typename InstanceType>
InstanceReference<InstanceType>::~InstanceReference() {
	_release();
}
template<typename InstanceType>
InstanceType *InstanceReference<InstanceType>::operator->() {
	ThrowMessageExceptionIfNULL(_ptr);
	return _ptr;
}
template<typename InstanceType>
const InstanceType *InstanceReference<InstanceType>::operator->() const {
	ThrowMessageExceptionIfNULL(_ptr);
	return _ptr;
}
template<typename InstanceType>
InstanceReference<InstanceType> &InstanceReference<InstanceType>::assign(InstanceType *ptr, InstanceReference<InstanceType>::DispatchTableIndex index, RetainAction action) {
	if(_ptr != ptr) {
		_release();
		_ptr= ptr;
		if(Retain == action) {
			_retain();
		}
	}
	_index= index;
	return *this;
}
template<typename InstanceType>
InstanceReference<InstanceType> &InstanceReference<InstanceType>::operator=(const InstanceReference<InstanceType>::InstanceReference &other) {
	if(this != &other) {
		return assign(other._ptr);
	}
	return *this;
}
template<typename InstanceType>
InstanceReference<InstanceType>::operator bool() const {
	return valid();
}
template<typename InstanceType>
bool InstanceReference<InstanceType>::valid() const {
	return NULL != _ptr;
}
template<typename InstanceType>
void InstanceReference<InstanceType>::_retain() {
	if(valid()) {
		_ptr->retain();
	}
}
template<typename InstanceType>
void InstanceReference<InstanceType>::_release() {
	if(valid()) {
		_ptr->release();
	}
}
template<typename InstanceType>
typename InstanceReference<InstanceType>::DispatchTableIndex InstanceReference<InstanceType>::dispatchTable() const {
	return _index;
}
template<typename InstanceType>
void InstanceReference<InstanceType>::dispatchTable(InstanceReference<InstanceType>::DispatchTableIndex index) {
	_index= index;
}

#endif // __InstanceReference_h__
