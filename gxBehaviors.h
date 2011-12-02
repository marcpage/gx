#ifndef __gxBehaviors_h__
#define __gxBehaviors_h__

#include "gxTypeSystem.h"
#include "gxInstances.h"
#include "os/ReferenceCounted.h"

class Behavior;
class Method;

class Object : public exec::ReferenceCounted::Ptr<Instance> {
	public:
		Object(const Behavior &expectedBehavior, Instance *instance, RetainAction action= Retain);
		Object(const Reference &other);
		~Object();
	private:
		size_t	_behavior;
};

#endif // __gxBehaviors_h__
