#ifndef __gxPointer_h__
#define __gxPointer_h__

#include "gxForwards.h"
#include "posix/MessageException.h"

#include <vector>
#include <string>

namespace gx {

	class Pointer {
		public:
			enum RetainAction {
				Retain,
				DoNotRetain
			};
			Pointer(Instance *instance, RetainAction action);
			Pointer(Instance *instance, const Text &interface, RetainAction action);
			Pointer(const Pointer &other);
			~Pointer();
			Pointer operator=(const Pointer &other);
			Pointer &assign(Instance *instance, RetainAction action);
			Pointer &assign(Instance *instance, const Text &interface, RetainAction action);
			bool valid() const;
			bool interface(Interface &interface) const;
			const Interface &interface() const;
			Pointer &castTo(const Text &interface);
			template<class T> T &ref();
			template<class T> const T &ref() const;
			template<class T> T *removeWithoutRelease();
		private:
			Instance	*_instance;
			uint32_t	_interface;
			static void _release(Instance *item);
			static Instance *_retain(Instance *item);
			void _set(Instance *other);
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
		return *dynamic_cast<const T*>(_instance);
	}
	template<class T> T* Pointer::removeWithoutRelease() {
		T	*instance= dynamic_cast<T*>(_instance);

		_instance= NULL;
		return instance;
	}
} // namespace gx

#endif // __gxPointer_h__
