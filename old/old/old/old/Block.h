#ifndef __Block_h__
#define __Block_h__

#include <vector>
class Block : public Instance {
	public:
		typedef NativeInteger::Integer		Index;
		typedef std::vector<InstanceRef>	InstanceList;
		Block();
		Index inputs() const;
		Index outputs() const;
	protected:
		virtual ~Block();
};

#endif // __Block_h__
