#ifndef __gxInstance_h__
#define __gxInstance_h__

#include "os/ReferenceCounted.h"

namespace type {
	class Type;
}

namespace gx {

	class Error;

	class Instance : public exec::ReferenceCounted {
		public:
			typedef exec::ReferenceCounted	Base;
			typedef Base					Super;
			typedef Super::Ptr<Instance>	Ptr;
			Instance(type::Type *type);
			type::Type *getType();
			const type::Type *getType() const;
			uint32_t getBehavior() const;
			uint32_t setBehavior(uint32_t behaviorId) const;
			Error *getError();
			bool setError(Error *error);
		protected:
			virtual ~Instance();
			virtual void free();
		private:
			type::Type	*_type;
			uint32_t	_behavior;
			Ptr			_error;
	};

	inline Instance(type::Type *type):_type(type), _behavior(0), _error(NULL) {}
	inline type::Type *getType() {return _type;}
	inline const type::Type *getType() const {return _type;}
	inline uint32_t getBehavior() const {return _behavior;}
	inline uint32_t setBehavior(uint32_t behaviorId) const {
		return util::assignAndReturnOriginal(_behavior, behaviorId);
	}
	inline Error *getError() {return reinterpret_cast<Error*>(&*_error);}
	inline bool setError(Error *error) {
		if( (NULL == error) || (NULL == _error) ) {
			_error= reinterpret_cast<Instance*>(error);
			return true;
		}
		return false;
	}
	inline Instance::~Instance() {}
	inline void Instance::free() {Super::free();}

}

#endif // __gxInstance_h__
