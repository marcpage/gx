#include "String.h"
#include "SubString.h"
#include "JoinString.h"
#include "ReferencedBuffer.h"
#include "ASCIIBufferString.h"
#include "posix/MessageException.h"
#include <locale>
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>

StringPtr String::substring(size_t offset) {
	return SubString::create(StringPtr(this), offset);
}
StringPtr String::substring(size_t offset, size_t subLength) {
	return SubString::create(StringPtr(this), offset, subLength);
}
StringPtr String::append(StringParam other) {
	return JoinString::create(StringPtr(this), other);
}
StringPtr String::remove(size_t offset) {
	return SubString::create(StringPtr(this), 0, offset);
}
StringPtr String::insert(StringParam substr, size_t beforeIndex) {
	const size_t	myLength= length();
	
	if(beforeIndex == 0) {
		return JoinString::create(substr, StringPtr(this));
	} else if(myLength == beforeIndex) {
		return JoinString::create(StringPtr(this), substr);
	}
	return JoinString::create(JoinString::create(substring(0, beforeIndex), substr), substring(beforeIndex));
}
StringPtr String::remove(size_t offset, size_t removalLength) {
	if(0 == offset) {
		return SubString::create(StringPtr(this), removalLength);
	} else if(offset + removalLength == length()) {
		return SubString::create(StringPtr(this), 0, offset);
	}
	return JoinString::create(
				SubString::create(StringPtr(this), 0, offset),
				SubString::create(StringPtr(this), offset + removalLength)
			);
}
int String::compare(StringParam substr) const {
	const size_t	l1= length();
	const size_t	l2= substr->length();
	const size_t	min= l1 < l2 ? l1 : l2;
	
	for(size_t index= 0; index < min; ++index) {
		if(at(index) < substr->at(index)) {
			return -1;
		} else if(at(index) > substr->at(index)) {
			return 1;
		}
	}
	if(l1 < l2) {
		return -1;
	} else if (l1 > l2) {
		return 1;
	}
	return 0;
}
StringPtr String::strip() {
	const size_t	myLength= length();
	size_t			leading;
	size_t			trailing;
	
	for(leading= 0; (leading < myLength) && (std::isspace(static_cast<wchar_t>(at(leading)))); ++leading) {
	}
	
	const size_t	maxtrailing= myLength - leading;
	
	for(trailing= 0; (trailing < maxtrailing) && (std::isspace(static_cast<wchar_t>(at(myLength - leading - 1)))); ++leading) {
	}
	return substring(leading, myLength - leading - trailing);
}
StringPtr String::stripStart() {
	const size_t	myLength= length();
	size_t			leading;
	
	for(leading= 0; (leading < myLength) && (std::isspace(static_cast<wchar_t>(at(leading)))); ++leading) {
	}
	return substring(leading);
}
StringPtr String::stripEnd() {
	const size_t	myLength= length();
	size_t			trailing;
	
	for(trailing= 0; (trailing < myLength) && (std::isspace(static_cast<wchar_t>(at(myLength - trailing - 1)))); ++trailing) {
	}
	return substring(0, myLength - trailing);
}
StringPtr String::replaceAll(StringParam substr, StringParam replace) {
	size_t			position= 0;
	const size_t	maxPosition= length();
	const size_t	substrLength= substr->length();
	StringPtr		result= ASCIIBufferString::create(ReferencedBuffer::create(NULL, 0));

	while(position < maxPosition) {
		const size_t	lastPosition= position;
		
		position= find(substr, position);
		if(position == String::npos) {
			result= result + substring(lastPosition);	// end of the string found
			position= maxPosition;
		} else if(position == lastPosition) {
			result= result + replace;	// nothing to put in result in this section (back to back matches)
		} else {
			result= result + substring(lastPosition, position - lastPosition) + replace;
			position+= substrLength; // skip past the substr
		}
	}
	return result;
}
inline size_t String::find(StringParam substr) const {
	return find(substr, 0);
}
inline size_t String::find(StringParam substr, size_t offset) const {
	const size_t	size= length();
	const size_t	substringSize= substr->length();
	
	AssertMessageException(offset < size);
	if(substringSize > size) {
		return npos;
	}
	for(size_t index= offset; index < size - substringSize; ++index) {
		bool	match= true;
		size_t	position;
		
		for(position= 0; match && (position < substringSize) && (index + position < size); ++position) {
			match= at(index + position) == substr->at(position);
		}
		if(match && (position == substringSize)) {
			return index;
		}
	}
	return npos;
}
inline size_t String::findFromEnd(StringParam substr) const {
	return findFromEnd(substr, length());
}
inline size_t String::findFromEnd(StringParam substr, size_t offset) const {
	const size_t	size= length();
	const size_t	substringSize= substr->length();
	
	AssertMessageException(offset <= size);
	if(substringSize > size) {
		return npos;
	}
	if(offset + substringSize > size) {
		offset= size - substringSize;
	}
	for(size_t index= offset; index > 0; --index) {
		bool	match= true;
		size_t	position;
		
		for(position= 0; match && (position < substringSize); ++position) {
			match= at(index + position) == substr->at(position);
		}
		if(match) {
			return index;
		}
	}
	return npos;
}
std::string &String::convert(std::string &buffer) const {
	std::wstring			wide;
	std::ostringstream		stm;
	const std::ctype<char>	&ctfacet= std::use_facet<std::ctype<char> >(stm.getloc());
	
	convert(wide);
	for(size_t i=0;	i < wide.size(); ++i) {
		stm << ctfacet.narrow(wide[i], 0);
	}
	buffer= stm.str();
	return buffer;
}
std::wstring &String::convert(std::wstring &buffer) const {
	std::string					narrow;
	std::wostringstream			wstm;
	const std::ctype<wchar_t>	&ctfacet= std::use_facet<std::ctype<wchar_t> >(wstm.getloc());
	
	convert(narrow);
	for(size_t i=0; i<narrow.size(); ++i) {
		wstm << ctfacet.widen(narrow[i]);
	}
	buffer= wstm.str();
	return buffer;
}
/** 
	@todo implement
*/
StringPtr String::insert(uint32_t character, size_t beforeIndex) const {
	
}
String::~String() {
}
