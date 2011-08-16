#include "gxGenericInstance.h"
#include "gxType.h"

GenericInstance::GenericInstance(const Type &actualType)
	:_type(actualType._instance) {
	if(NULL != _type) {
		_type->retain();
	}
}
/** 
	@todo implement
*/
bool GenericInstance::is(const Type &actualType) {
}
/** 
	@todo implement
*/
bool GenericInstance::does(const Interface &interface) {
}
GenericInstance::~GenericInstance() {
	if(NULL != _type) {
		_type->release();
	}
}
/** 
	@todo implement
*/
GenericInstance *GenericInstance::clone() {
}
