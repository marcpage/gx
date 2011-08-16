#ifndef __gxIntrinsicInterface_h__
#define __gxIntrinsicInterface_h__

#include "gxIntrinsic.h"
#include "gxType.h"
#include "gxInterface.h"
#include "gxText.h"
#include "gxPrototype.h"
#include <vector>

namespace gx {

	class IntrinsicInterface : public Intrinsic {
		public:
			IntrinsicInterface(const Text &name, const Type &intrinsicInterface);
			const Text name() const;
			uint32_t add(const Prototype &prototype);
			uint32_t count() const;
			uint32_t find(const Text &name) const;
			const Prototype &get(uint32_t index) const;
			uint32_t add(const Text &name, const Pointer &value); ///< constant
			IntrinsicInterface &implementation(uint32_t methodIndex, uint32_t constantIndex);
		protected:
			virtual ~IntrinsicInterface();
		private:
			typedef std::vector<Prototype>		PrototypeList;
			typedef std::pair<Text,Pointer>		NamedInstance;
			typedef std::vector<NamedInstance>	InstanceList;
			typedef std::vector<uint32_t>		IndexList;
			Text			_name;
			PrototypeList	_prototypes;
			InstanceList	_constants;
			IndexList		_defaults;
	};

} // namespace gx

#endif // __gxIntrinsicInterface_h__
