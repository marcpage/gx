#include "gxIntrinsicPrototype.h"

namespace gx {

	IntrinsicPrototype::IntrinsicPrototype(const Type &actualType, const Text &name)
		:Intrinsic(actualType), _name(name), _parameters() {
	}
	IntrinsicPrototype &IntrinsicPrototype::add(Direction direction, const Text &name, const Interface &type) {
		_parameters[direction].push_back(NamedType(name, type));
	}
	uint32_t IntrinsicPrototype::count(Direction direction) const {
		return _parameters[direction].size();
	}
	const Type &IntrinsicPrototype::parameter(uint32_t index) const {
		return _parameters[direction][index].second;
	}
	const Text &IntrinsicPrototype::name(uint32_t index) const {
		return _parameters[direction][index].first;
	}
	IntrinsicPrototype::~IntrinsicPrototype() {
	}

} // namespace gx
