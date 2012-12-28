#include "gxPointer.h"
#include "gxInterface.h"
#include "gxGenericInstance.h"

Pointer::Pointer(GenericInstance *instance, RetainAction action)
	:_instance(instance), _interface(NULL) {
	if(Retain == action) {
		_retain(_instance);
	}
}
Pointer::Pointer(GenericInstance *instance, const Interface &interface, RetainAction action)
	:_instance(instance), _interface(const_cast<GenericInstance*>(&interface.ref<GenericInstance>())) {
	_retain(_interface);
	if(Retain == action) {
		_retain(_instance);
	}
}
Pointer::Pointer(const Pointer &other)
	:_instance(other._instance), _interface(other._interface) {
	_retain(_instance);
	_retain(_interface);
}
Pointer::~Pointer() {
	_release(_instance);
	_release(_interface);
}
Pointer &Pointer::operator=(const Pointer &other) {
	if(this != &other) {
		_release(_instance);
		_release(_interface);
		_instance= other._instance;
		_interface= other._interface;
		_retain(_instance);
		_retain(_interface);
	}
}
Pointer &Pointer::assign(GenericInstance *instance, RetainAction action) {
	_release(_instance);
	_release(_interface);
	_instance= instance;
	_interface= NULL;
	if(Retain == action) {
		_retain(_instance);
	}
}
Pointer &Pointer::assign(GenericInstance *instance, const Interface &interface, RetainAction action) {
	_release(_instance);
	_release(_interface);
	_instance= instance;
	_interface= const_cast<GenericInstance*>(&interface.ref<GenericInstance>());
	if(Retain == action) {
		_retain(_instance);
	}
}
void Pointer::getInterface(Interface &interface) const {
	if(NULL == _interface) {
		interface.assign(NULL, DoNotRetain);
	} else {
		interface.assign(_interface, Interface::interface, Retain);
	}
}
/** 
	@todo implement
	need to check to see if this object supports the given interface
*/
void Pointer::castTo(const Interface &interface) {
}
void Pointer::_release(GenericInstance *item) {
	if(NULL != item) {
		item->release();
	}
}
void Pointer::_retain(GenericInstance *item) {
	if(NULL != item) {
		item->retain();
	}
}
