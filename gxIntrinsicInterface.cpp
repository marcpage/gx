#include "gxIntrinsicInterface.h"

namespace gx {

	IntrinsicInterface::IntrinsicInterface(const Text &name, const Type &intrinsicInterface)
		:Intrinsic(intrinsicInterface), _name(name), _prototypes(), _constants(), _defaults() {
	}
	const Text IntrinsicInterface::name() const {
		return _name;
	}
	uint32_t IntrinsicInterface::add(const Prototype &prototype) {
		_prototypes.push_back(prototype);
		return _prototypes.size() - 1;
	}
	uint32_t IntrinsicInterface::count() const {
		return static_cast<uint32_t>(_prototypes.size());
	}
	uint32_t IntrinsicInterface::find(const Text &name) const {
		ThrowMessageException("TODO: NEED TO IMPLEMENT");
	}
	const Prototype &IntrinsicInterface::get(uint32_t index) const {
		return _prototypes[index];
	}
	uint32_t IntrinsicInterface::add(const Text &name, const Pointer &value) {
		_constants.push_back(NamedInstance(name, value));
		return _constants.size() - 1;
	}
	IntrinsicInterface &IntrinsicInterface::implementation(uint32_t methodIndex, uint32_t constantIndex) {
		if(_defaults.size() <= methodIndex) {
			_defaults.resize(methodIndex + 1);
		}
		_defaults[methodIndex]= constantIndex;
		return *this;
	}
	IntrinsicInterface::~IntrinsicInterface() {
	}

} // namespace gx
