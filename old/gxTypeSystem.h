#ifndef __gxTypeSystem_h__
#define __gxTypeSystem_h__

#include "gxInstances.h"
#include <map>

class TypeSystem {
	public:
		/// @todo Add IntegerUnbounded and DoubleDouble?
		enum BasicTypes {
			// Intrinsics
			tList,		tMap,			tDouble,	tInteger64,	tBuffer,
			tReference,
			// Extrinsics
			tType,			tBehavior,	tDispatch,		tInterface,	tMethod,
			tNativeMethod,	tCode,		tOrderedMap,	tASCIIText,
			TypeCount
		};
		enum BasicBehaviors {
			bNumber,	bInteger,	bCharacter,		bBoolean,		bReal,
			bText,		bBuffer,	bReference,		bBehavior,		bType,
			bInterface,	bMethod,	bList,			bMap,			bObject,
			bDispatch,	bHashable,	bDisplayable,	bSerializable,	bComparable,
			bOrderedMap,
			BehaviorCount
		};
		TypeSystem();
		~TypeSystem();
		Instance *getType(const char *name);
		Instance *getType(BasicTypes type);
		Instance *getBehavior(const char *name);
		Instance *getBehavior(BasicBehaviors type);
		void add(Instance *type);
	private:
		typedef std::map<std::string, Instance*>	Map;
		Map	_types;
		Map	_behaviors;
		void _startTypeInit();
		void _startBehaviorInit();
		void _initTypeInstanceMembers();
		Instance *_lookupParent(BasicTypes type);
		ExtrinsicInstance *_createText(const char * const text);
};

#endif // __gxTypeSystem_h__
