#ifndef __Extrinsic_h__
#define __Extrinsic_h__

#include "gxGenericInstance.h"
#include <vector> ///< for std::vector

class Extrinsic : public GenericInstance {
	public:
		Extrinsic(const Type &theType, size_t memberCount);
		Pointer &operator[](size_t index);
	protected:
		~Extrinsic() {}
	private:
		std::vector<Pointer>	_members;
};

#endif // __Extrinsic_h__
