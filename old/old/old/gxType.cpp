#include "gxExtrinsic.h"
#include "gxFloat.h"
#include "gxInteger64Bit.h"
#include "gxBuffer.h"
#include "gxInterprettedCode.h"
#include "gxNativeCode.h"
#include "gxList.h"
#include "gxReference.h"
#include "gxInstance.h"
#include "gxType.h"
#include "gxASCIIText.h"
#include "gxDispatch.h"
#include "gxInterface.h"
#include "gxMethod.h"
#include "gxPrototype.h"
#include "gxNamedType.h"
#include "gxNamedInstance.h"

const Type Type::type;
const Interface Type::interface;

#define TypeTableEntry(x, i) {"gx."#x, &x::type, &x::interface, i, x::init, x::kCountOfMembers, x::kCountOfConstants}

enum Interfaces {
	iInstance,
	iDisplayable,
	iNumber,
	iInteger,
	iCode,
	iBuffer,
	iList,
	iReference,
	iType,
	iText,
	iDispatch,
	iInterface,
	iMethod,
	iPrototype,
	iNamedType,
	iNamedInstance,
	kInterfaceCount
};
Interface gInterfaceBootStrapTable[kInterfaceCount];

struct BootStrapEntry {
	const char			*name;
	const Type 			*type;
	const Interface 	*interface;
	size_t				interfaceIndex;
	void				(*init)();
	size_t				memberCount;
	size_t				constantCount;
} gTypeBootStrapTable[]= {
	TypeTableEntry(Float, iNumber),
	TypeTableEntry(Integer64Bit, iInteger),
	TypeTableEntry(Buffer, iBuffer),
	TypeTableEntry(InterprettedCode, iCode),
	TypeTableEntry(NativeCode, iCode),
	TypeTableEntry(List, iList),
	TypeTableEntry(Reference, iReference),
	TypeTableEntry(Instance, iInstance),
	TypeTableEntry(Type, iType),
	TypeTableEntry(ASCIIText, iText),
	TypeTableEntry(Dispatch, iDispatch),
	TypeTableEntry(Interface, iInterface),
	TypeTableEntry(Method, iMethod),
	TypeTableEntry(Prototype, iPrototype),
	TypeTableEntry(NamedType, iNamedType),
	TypeTableEntry(NamedInstance, iNamedInstance),
};

/** 
	@todo Still to setup
		Dispatch table methods
		Interface prototypes
		
*/
void Type::init() {
	static bool	inited= false;
	
	if(!inited) {
		Type	placeHolderType;
		
		inited= true;
		// create the types
		for(size_t type= 0; type < sizeof(gTypeBootStrapTable)/sizeof(gTypeBootStrapTable[0]); ++type) {
			const_cast<Type*>(gTypeBootStrapTable[type].type)->assign(new Extrinsic(placeHolderType, Type::kCountOfMembers), Pointer::DoNotRetain);
		}
		// create the interfaces
		for(size_t interface= 0; interface < sizeof(gInterfaceBootStrapTable)/sizeof(gInterfaceBootStrapTable[0]); ++interface) {
			gInterfaceBootStrapTable[interface].assign(new Extrinsic(Interface::type, Interface::kCountOfMembers), Pointer::DoNotRetain);
		}
		// assign interface of all interfaces
		for(size_t interface= 0; interface < sizeof(gInterfaceBootStrapTable)/sizeof(gInterfaceBootStrapTable[0]); ++interface) {
			gInterfaceBootStrapTable[interface]._interface= &gInterfaceBootStrapTable[iInterface].ref<GenericInstance>();
			Pointer::_retain(gInterfaceBootStrapTable[interface]._interface);
		}
		// initialize all Pointer types and interfaces
		for(size_t type= 0; type < sizeof(gTypeBootStrapTable)/sizeof(gTypeBootStrapTable[0]); ++type) {
			size_t	index= gTypeBootStrapTable[type].interfaceIndex;

			*const_cast<Type*>(gTypeBootStrapTable[type].type)= const_cast<GenericInstance*>(&Type::type.ref<GenericInstance>());
			*const_cast<Interface*>(gTypeBootStrapTable[type].interface)= gInterfaceBootStrapTable[index];
		}
		// set the name, parent and dispatches (and fill in interface of the dispatch)
		for(size_t type= 0; type < sizeof(gTypeBootStrapTable)/sizeof(gTypeBootStrapTable[0]); ++type) {
			size_t	index= gTypeBootStrapTable[type].interfaceIndex;
			List	dispatches(1);
			List	members(gTypeBootStrapTable[type].memberCount);
			List	constants(gTypeBootStrapTable[type].constantCount);
			
			dispatches.set(0, Dispatch(gInterfaceBootStrapTable[index]));
			const_cast<Type*>(gTypeBootStrapTable[type].type)->ref<Extrinsic>()[Name]= ASCIIText(gTypeBootStrapTable[type].name);
			const_cast<Type*>(gTypeBootStrapTable[type].type)->ref<Extrinsic>()[Parent]= Instance::type;
			const_cast<Type*>(gTypeBootStrapTable[type].type)->ref<Extrinsic>()[Dispatches]= dispatches;
			const_cast<Type*>(gTypeBootStrapTable[type].type)->ref<Extrinsic>()[Constants]= constants;
			const_cast<Type*>(gTypeBootStrapTable[type].type)->ref<Extrinsic>()[Members]= members;
		}
		
		// Fill in a list of all the known types so far
		List		typeList(sizeof(gTypeBootStrapTable)/sizeof(gTypeBootStrapTable[0]));
		
		for(size_t type= 0; type < sizeof(gTypeBootStrapTable)/sizeof(gTypeBootStrapTable[0]); ++type) {
			typeList.set(type, *gTypeBootStrapTable[type].type);
		}
		
		Type		*typeType= const_cast<Type*>(&Type::type); ///< Get Type's type to fix up
		List		&members= typeType->ref<Extrinsic>()[Members].ref<List>();
		List		&constants= typeType->ref<Extrinsic>()[Constants].ref<List>();
		Reference	allTypes(typeList);
		
		members.set(Name,		gInterfaceBootStrapTable[iText]);
		members.set(Parent,		gInterfaceBootStrapTable[iType]);
		members.set(Dispatches,	gInterfaceBootStrapTable[iList]);
		members.set(Constants,	gInterfaceBootStrapTable[iList]);
		members.set(Members,	gInterfaceBootStrapTable[iList]);
		constants.set(AllTypes,	allTypes);
		
		// call the init for every type
		for(size_t type= 0; type < sizeof(gTypeBootStrapTable)/sizeof(gTypeBootStrapTable[0]); ++type) {
			gTypeBootStrapTable[type].init();
		}
	}
}
