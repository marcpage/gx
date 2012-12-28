#include "posix/MessageException.h"

StringPtr SubString::create(StringParam theString, size_t offset) {
	const size_t	theStringLength= theString->length();
	
	AssertMessageException(offset <= theStringLength);
	return StringPtr(new SubString(theString, offset, theStringLength - offset));
}
StringPtr SubString::create(StringParam theString, size_t offset, size_t length) {
	const size_t	theStringLength= theString->length();
	
	AssertMessageException(offset <= theStringLength);
	AssertMessageException(offset + length <= theStringLength);
	return StringPtr(new SubString(theString, offset, length));
}
uint32_t SubString::at(size_t index) const {
	AssertMessageException(index < _length);
	return _master->at(_offset + index);
}
size_t SubString::find(StringParam substr) const {
	return find(substr, 0);
}
size_t SubString::find(StringParam substr, size_t offset) const {
	size_t	found= _master->find(substr, _offset + offset);
	
	if(String::npos == found) {
		return found;
	}
	if(found - _offset + substr->length() >= _length) {
		return String::npos;
	}
	return found - _offset;
}
size_t SubString::findFromEnd(StringParam substr) const {
	return findFromEnd(substr, length());
}
size_t SubString::findFromEnd(StringParam substr, size_t offset) const {
	size_t	found;
	
	do	{
		found= _master->findFromEnd(substr, _offset + offset);
		if(String::npos == found) {
			return found;
		} else if(found - _offset + substr->length() < _length) {
			return found - _offset;
		} else {
			--found;
		}
	} while(true);
}
/** 
	@todo handle multibyte strings better?
	@todo dump for wchar_t*? (std::wstring)
*/
std::string &SubString::convert(std::string &buffer) {
	_master->convert(buffer);
	buffer.erase(_offset + _length);
	buffer.erase(0, _offset);
	return buffer;
}
size_t SubString::length() const {
	return _length;
}
size_t SubString::parts() const {
	return _master->parts();
}
SubString::SubString(StringParam master, size_t offset, size_t substringLength)
	:_master(master), _offset(offset), _length(substringLength) {
}
SubString::~SubString() {
}
