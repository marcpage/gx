#ifndef __gxIntrinsicType_h__
#define __gxIntrinsicType_h__

#include "gxIntrinsic.h"
#include "gxType.h"
#include "gxText.h"
#include "gxInterface.h"
#include <vector>

namespace gx {

	class IntrinsicType : public Intrinsic {
		public:
			IntrinsicType(const Text &theName, const Type &typeType, const Type &theParent);
			uint32_t add(const Interface &type);
			const Type &parent() const;
			IntrinsicType &connect(uint32_t interface, uint32_t methodIndex, uint32_t constantIndex);
			uint32_t add(const Text &name, const Pointer &value); ///< constant
			uint32_t add(const Type &type, const Text &name); ///< member
			uint32_t member(const Text &name) const;
			const Type &member(uint32_t index) const;
			const Text &memberName(uint32_t index) const;
			const Text &name() const;
			uint32_t interface(const Text &name) const;
			const Interface &interface(uint32_t index) const;
			uint32_t method(uint32_t interfaceIndex, uint32_t methodIndex);
			uint32_t constant(const Text &name) const;
			template<class T> const T &constant(uint32_t index) const;
		protected:
			virtual ~IntrinsicType();
		private:
			friend class TypeSystem;
			typedef std::vector<uint32_t>				IntegerList;
			typedef std::pair<Text,Type>				NamedType;
			typedef std::vector<NamedType>				TypeList;
			typedef std::pair<Text,Pointer>				NamedInstance;
			typedef std::vector<NamedInstance>			InstanceList;
			typedef std::pair<Interface,IntegerList>	DispatchTable;
			typedef std::vector<DispatchTable>			DispatchList;
			static TypeList	_types;
			Text			_name;
			Type			_parent;
			TypeList		_contents;
			InstanceList	_constants;
			DispatchList	_dispatch;
	};

	/**
		@todo assert the index is in range
	*/
	template<class T> const T &IntrinsicType::constant(uint32_t index) const {
		return T(_constants[index].second);
	}

} // namespace gx

#endif // __gxIntrinsicType_h__
