#include "gxExtrinsic.h"
#include "gxPointer.h"
#include "posix/MessageException.h"

Extrinsic::Extrinsic(const Type &theType, size_t memberCount)
	:GenericInstance(theType), _members(memberCount) {
}
Pointer &Extrinsic::operator[](size_t index) {
	AssertMessageException( (index >= 0) && (index < _members.size()) );
	return _members[index];
}
