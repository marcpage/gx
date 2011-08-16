#ifndef __gxIntrinsicPrototype_h__
#define __gxIntrinsicPrototype_h__

#include "gxInstance.h"
#include "gxInterface.h"
#include "gxText.h"
#include <vector>

namespace gx {

	class IntrinsicPrototype : public Intrinsic {
		public:
			enum Direction {
				Input,
				Output,
				DirectionCount
			};
			IntrinsicPrototype(const Type &actualType, const Text &name);
			IntrinsicPrototype &add(Direction direction, const Text &name, const Interface &type);
			uint32_t count(Direction direction) const;
			const Type &parameter(uint32_t index) const;
			const Text &name(uint32_t index) const;
		protected:
			virtual ~IntrinsicPrototype();
		private:
			typedef std::pair<Text,Type>	NamedType;
			typedef std::vector<NamedType>	NamedTypeList;
			Text			_name;
			NamedTypeList	_parameters[DirectionCount];
	};

} // namespace gx

#endif // __gxIntrinsicPrototype_h__
