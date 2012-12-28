#ifndef _ReferenceCounted_h_
#define _ReferenceCounted_h_

#include "posix/MessageException.h"

class ReferenceCounted {
	public:
		int32_t retain();
		void release();
		int32_t references() const;
	protected:
		ReferenceCounted();
		ReferenceCounted(const ReferenceCounted &other);
		ReferenceCounted &operator=(const ReferenceCounted &other);
		virtual ~ReferenceCounted();
	private:
		int32_t	_count;
};

#include "ReferenceCounted.hpp"

#endif // _ReferenceCounted_h_
