#include "gxList.h"
#include "gxType.h"
#include "gxInterface.h"
#include "gxIntrinsicList.h"

const Type List::type;
const Interface List::interface;

void List::init() {
}
List::List(size_t actualSize)
	:Pointer(new IntrinsicList(actualSize), interface, DoNotRetain) {
}
List::List(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, action) {
}
/** 
	@todo Implement
*/
size_t List::size() const {
}
void List::get(size_t index, Pointer &value) {
	ref<IntrinsicList>().get(index, value);
}
/** 
	@todo Implement
*/
void List::set(size_t index, const Pointer &value) {
}
