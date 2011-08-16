#ifndef __gxForwards_h__
#define __gxForwards_h__

/**
	@todo Make as many Instrinsics Extrinsic as possible
*/
namespace gx {

	// These are used by the runtime
	class Instance; // these are concrete types
		class Intrinsic;
			class IntrinsicType;
			class IntrinsicInterface;
			class IntrinsicInteger;
			class IntrinsicReal;
			class IntrinsicBuffer;
			class IntrinsicList;
			class IntrinsicReference;
			class IntrinsicASCIIText;
			class IntrinsicNativeMethod;
		class Extrinsic;

	// These are helper classes to help in C++ programming
	class Pointer; // these are interface handlers
		class Type;
		class Interface;
		class Character;
		class Number;
			class Integer;
			class Real;
		class Buffer;
		class Text;

} // namespace gx

#endif // __gxForwards_h__
