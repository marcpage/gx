#include "gxIntrinsicType.h"
#include "gxIntrinsicInterface.h"

namespace gx {

	IntrinsicType::IntrinsicType(const Text &theName, const Type &typeType, const Type &theParent)
		:Intrinsic(typeType), _name(theName), _parent(theParent), _contents(), _constants(), _dispatch() {
	}
	/**
		@todo sanity check
	*/
	uint32_t IntrinsicType::add(const Interface &type) {
		_dispatch.push_back(DispatchTable(type, IntegerList(type.ref<IntrinsicInterface>().count())));
		return _dispatch.size() - 1;
	}
	const Type &IntrinsicType::parent() const {
		return _parent;
	}
	IntrinsicType &IntrinsicType::connect(uint32_t interface, uint32_t methodIndex, uint32_t constantIndex) {
		_dispatch[interface].second[methodIndex]= constantIndex;
		return *this;
	}
	uint32_t IntrinsicType::add(const Text &name, const Pointer &value) {
		_constants.push_back(NamedInstance(name, value));
		return _constants.size() - 1;
	}
	uint32_t IntrinsicType::add(const Type &type, const Text &name) {
		_contents.push_back(NamedType(name, type));
		return _contents.size() - 1;
	}
	uint32_t IntrinsicType::member(const Text &name) const {
		for(TypeList::const_iterator m= _contents.begin(); m != _contents.end(); ++m) {
			if(m->first.equals(name)) {
				return m - _contents.begin();
			}
		}
		return static_cast<uint32_t>(-1);
	}
	/**
		@todo assert index in range
	*/
	const Type &IntrinsicType::member(uint32_t index) const {
		return _contents[index].second;
	}
	const Text &IntrinsicType::memberName(uint32_t index) const {
		return _contents[index].first;
	}
	const Text &IntrinsicType::name() const {
		return _name;
	}
	uint32_t IntrinsicType::interface(const Text &name) const {
		for(DispatchList::const_iterator m= _dispatch.begin(); m != _dispatch.end(); ++m) {
			if(m->first.ref<IntrinsicInterface>().name().equals(name)) {
				return m - _dispatch.begin();
			}
		}
		return static_cast<uint32_t>(-1);
	}
	/**
		@todo validate index
	*/
	const Interface &IntrinsicType::interface(uint32_t index) const {
		return _dispatch[index].first;
	}
	/**
		@todo validate indexes
	*/
	uint32_t IntrinsicType::method(uint32_t interfaceIndex, uint32_t methodIndex) {
		return _dispatch[interfaceIndex].second[methodIndex];
	}
	uint32_t IntrinsicType::constant(const Text &name) const {
		for(InstanceList::const_iterator m= _constants.begin(); m != _constants.end(); ++m) {
			if(m->first.equals(name)) {
				return m - _constants.begin();
			}
		}
		return static_cast<uint32_t>(-1);
	}
	IntrinsicType::~IntrinsicType() {
	}

} // namespace gx

