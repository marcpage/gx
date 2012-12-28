#ifndef __Pointer_h__
#define __Pointer_h__

#include "gxForwardDeclares.h"
#include "posix/MessageException.h"

class Pointer {
	public:
		enum RetainAction {
			Retain,
			DoNotRetain
		};
		Pointer(GenericInstance *instance= NULL, RetainAction action= Retain);
		Pointer(GenericInstance *instance, const Interface &interface, RetainAction action= Retain);
		Pointer(const Pointer &other);
		~Pointer();
		Pointer &operator=(const Pointer &other);
		Pointer &assign(GenericInstance *instance, RetainAction action);
		Pointer &assign(GenericInstance *instance, const Interface &interface, RetainAction action);
		void getInterface(Interface &interface) const;
		void castTo(const Interface &interface);
		template<class T>
		T &ref();
		template<class T>
		const T &ref() const;
		template<class T>
		T *removeWithoutRelease();
	private:
		GenericInstance	*_instance;
		GenericInstance	*_interface;
		friend class Type; ///< used for bootstrapping
		friend class GenericInstance; ///< used for bootstrapping
		
		static void _release(GenericInstance *item);
		static void _retain(GenericInstance *item);
	    void *operator new(size_t); ///< Prevent usage
		void operator delete(void*); ///< Prevent usage
	    void *operator new[](size_t); ///< Prevent usage
		void operator delete[](void*); ///< Prevent usage
};

template<class T> T &Pointer::ref() {
	ThrowMessageExceptionIfNULL(_instance);
	return *dynamic_cast<T*>(_instance);
}
template<class T> const T &Pointer::ref() const {
	ThrowMessageExceptionIfNULL(_instance);
	return *dynamic_cast<T*>(_instance);
}
template<class T>
T *Pointer::removeWithoutRelease() {
	T	*instance= dynamic_cast<T*>(_instance);
	
	_instance= NULL;
	return instance;
}

#endif // __Pointer_h__
