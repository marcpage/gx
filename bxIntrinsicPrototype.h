#ifndef __gxIntrinsicPrototype_h__
#define __gxIntrinsicPrototype_h__

#include "gxIntrinsic.h"
#include "gxType.h"
#include "gxPrototype.h"
#include "gxText.h"
#include <vector>

namespace gx {

	class IntrinsicPrototype : public Intrinsic {
		public:
			enum Direction {
				Input,
				Output
			};
			IntrinsicPrototype(const Text &name);
			void add(Direction direction, const Type &type, const Text &name);
			uint32_t count(Direction direction);
			uint32_t find(Direction direction, const Text &name);
			const Type &get(Direction direction, uint32_t index);
			const Text &getName(Direction direction, uint32_t index);
		protected:
			virtual ~IntrinsicPrototype();
		private:
			typedef std::pair<Text,Type>	NamedType;
			typedef std::vector<NamedType>	TypeList;
			Text		_name;
			TypeList	_inputs;
			TypeList	_outputs;
	};

} // namespace gx

#endif // __gxIntrinsicPrototype_h__
