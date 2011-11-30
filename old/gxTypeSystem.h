#ifndef __gxTypeSystem_h__
#define __gxTypeSystem_h__

#include <vector>
#include "gxType.h"
#include "gxInterface.h"

namespace gx {
	class TypeSystem {
		public:
			TypeSystem();
			~TypeSystem();
			TypeSystem &add(const Type &aType);
			TypeSystem &add(const Interface &anInterface);
			bool get(const Text &name, Type &theType) const;
			bool get(const Text &name, Interface &theInterface) const;
			void remove(const Type &theType);
			void remove(const Interface &theInterface);
		private:
			typedef std::vector<Type>		TypeList;
			typedef std::vector<Interface>	InterfaceList;
			TypeList		_types;
			InterfaceList	_interfaces;
			TypeSystem(const TypeSystem&); ///< Prevent usage
			TypeSystem &operator=(const TypeSystem&); ///< Prevent usage
	};
} // namespace gx

#endif // __gxTypeSystem_h__
