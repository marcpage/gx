#ifndef _SmartPtr_h_
#define _SmartPtr_h_

template<class T>
class SmartPtr {
	public:
		explicit SmartPtr(T *p= NULL);
		SmartPtr(const SmartPtr<T> &other);
		~SmartPtr();
		SmartPtr &operator=(const SmartPtr<T> &other);
		T &operator*() const;
		T *operator->() const;
		operator bool() const;
		int32_t retain() const;
		void release() const;
		int32_t references() const;
		template<class O>
		SmartPtr<O> cast() const; ///< Dynamic cast
	private:
		T	*_p;
};

#include "SmartPtr.hpp"

#endif // _SmartPtr_h_
