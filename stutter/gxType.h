#ifndef __gxType_h__
#define __gxType_h__

#include "gxInstance.h"
#include <vector>
#include <string>

namespace gx {

	class Type : public Instance {
		public:
			Type(const std::string &name);
		protected:
			virtual ~Type();
		private:
			struct DispatchTable {
				std::string	name;

			};
			typedef std::vector<Type*>					TypeList;
			typedef std::vector<Instance*>				InstanceList;
			typedef std::pair<std::string,Interface*>	NamedInterface;
			typedef std::vector<NamedInterface>			InterfaceList;
			static TypeList	_types;
			std::string		_name;
			TypeList		_contents;
			InstanceList	_constants;
			InterfaceList	_
	};

} // namespace gx

#endif // __gxType_h__
