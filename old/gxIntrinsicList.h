#ifndef __IntrinsicList_h__
#define __IntrinsicList_h__

#include "gxIntrinsic.h"
#include <vector> ///< For std::vector

class IntrinsicList : public Intrinsic {
	public:
		IntrinsicList(size_t actualSize);
		void get(size_t index, Pointer &value);
	protected:
		virtual ~IntrinsicList() {}
	private:
		std::vector<Pointer>	_values;
};

#endif // __IntrinsicList_h__
