#ifndef __gxIntrinsicASCIIText_h__
#define __gxIntrinsicASCIIText_h__

#include "gxIntrinsic.h"
#include "gxType.h"
#include "gxInterface.h"
#include "gxText.h"
#include "gxInterinsicText.h"

namespace gx {

	class IntrinsicASCIIText : public IntrinsicText {
		public:
			typedef void (*Dispose)(const void *p);
			IntrinsicASCIIText(const Type &actualType, const void *buffer, size_t length, Dispose action);
			virtual uint32_t length() const;
			virtual uint32_t character(uint32_t index) const;
		protected:
			virtual ~IntrinsicASCIIText();
		private:
			const void	*_buffer;
			size_t		_length;
			Dispose		_action;
	};

} // namespace gx

#endif // __gxIntrinsicASCIIText_h__
