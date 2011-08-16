#include "gxIntrinsicList.h"
#include "gxList.h"

IntrinsicList::IntrinsicList(size_t actualSize)
	:Intrinsic(List::type), _values(actualSize) {
}
void IntrinsicList::get(size_t index, Pointer &value) {
	AssertMessageException( (index >= 0) && (index < _values.size()) );
	value= _values[index];
}
