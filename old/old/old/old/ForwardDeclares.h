#ifndef _ForwardDeclares_h_
#define _ForwardDeclares_h_

#include "SmartPtr.h"

class ReferenceCounted;
class Interface;
class Type;
class Behavior;
class DispatchTable;
class Implementation;
class ByteCodeImplementation;
class NativeImplementation;
class Buffer;
class AllocatedBuffer;
class ReferencedBuffer;
class SubBuffer;
class Instance;
class String;
class ASCIIBufferString;
class TermedBehavior;
class JoinString;
class SubString;
class TypeSystem;
template<class T> class Named;

#define MakeSmartPtr(c) typedef SmartPtr<c> c##Ptr
	MakeSmartPtr(String);
	MakeSmartPtr(Behavior);
	MakeSmartPtr(Interface);
	MakeSmartPtr(Implementation);
	MakeSmartPtr(DispatchTable);
	MakeSmartPtr(Type);
	MakeSmartPtr(Instance);
	MakeSmartPtr(TermedBehavior);
	MakeSmartPtr(AllocatedBuffer);
	MakeSmartPtr(ASCIIBufferString);
	MakeSmartPtr(TypeSystem);
	MakeSmartPtr(Buffer);
#undef MakeSmartPtr

#define MakeParam(c) typedef const SmartPtr<c> &c##Param
	MakeParam(String);
	MakeParam(Behavior);
	MakeParam(Interface);
	MakeParam(Implementation);
	MakeParam(DispatchTable);
	MakeParam(Type);
	MakeParam(Instance);
	MakeParam(TermedBehavior);
	MakeParam(AllocatedBuffer);
	MakeParam(ASCIIBufferString);
	MakeParam(TypeSystem);
	MakeParam(Buffer);
#undef MakeParam

#endif // _ForwardDeclares_h_
