#include "gxPointer.h"
#include "gxInstance.h"
#include "gxIntrinsicType.h"

namespace gx {

	Pointer::Pointer(Instance *instance, RetainAction action)
		:_instance(instance), _interface(0) {
		if(Retain == action) {
			_retain(_instance);
		}
	}
	Pointer::Pointer(Instance *instance, const Text &interface, RetainAction action)
		:_instance(instance), _interface(0) {
		if(Retain == action) {
			_retain(_instance);
		}
		if(valid() && _instance->type().valid()) {
			_interface= _instance->type().ref<IntrinsicType>().interface(interface);
		}
	}
	Pointer::Pointer(const Pointer &other)
		:_instance(_retain(other._instance)), _interface(other._interface) {
	}
	Pointer::~Pointer() {
		_release(_instance);
	}
	Pointer Pointer::operator=(const Pointer &other) {
		if(this != &other) {
			_set(other._instance);
			_interface= other._interface;
		}
		return *this;
	}
	Pointer &Pointer::assign(Instance *instance, RetainAction action) {
		_set(instance);
		_interface= 0;
		return *this;
	}
	Pointer &Pointer::assign(Instance *instance, const Text &interface, RetainAction action) {
		_set(instance);
		if(valid() && _instance->type().valid()) {
			_interface= _instance->type().ref<IntrinsicType>().interface(interface);
		} else {
			_interface= 0;
		}
		return *this;
	}
	/**
		@todo add interface index checking also?
	*/
	bool Pointer::valid() const {
		return (NULL != _instance);
	}
	bool Pointer::interface(Interface &interface) const {
		if(valid() && _instance->type().valid()) {
			interface= _instance->type().ref<IntrinsicType>().interface(_interface);
			return true;
		}
		return false;
	}
	/**
		@todo assert that the interface exists
	 */
	const Interface &Pointer::interface() const {
		AssertMessageException(valid());
		AssertMessageException(_instance->type().valid());
		return _instance->type().ref<IntrinsicType>().interface(_interface);
	}
	/**
		@todo ensure interface is found
	*/
	Pointer &Pointer::castTo(const Text &interface) {
		AssertMessageException(valid());
		AssertMessageException(_instance->type().valid());
		_interface= _instance->type().ref<IntrinsicType>().interface(interface);
		return *this;
	}
	void Pointer::_release(Instance *item) {
		if(NULL != item) {
			item->release();
		}
	}
	Instance *Pointer::_retain(Instance *item) {
		if(NULL != item) {
			item->retain();
		}
		return item;
	}
	void Pointer::_set(Instance *other) {
		if(_instance != other) {
			_release(_instance);
			_instance= _retain(other);
		}
	}

} // namespace gx
