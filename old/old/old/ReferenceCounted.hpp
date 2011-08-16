inline ReferenceCounted::ReferenceCounted()
	:_count(1) {
}
inline ReferenceCounted::~ReferenceCounted() {
	AssertMessageException(_count == 0);
}
/** 
	@todo Make this Atomic Increment
*/
inline int32_t ReferenceCounted::retain() {
	AssertMessageException(_count > 0);
	++_count;
	return _count;
}
/** 
	@todo Make this Atomic Decrement
*/
inline void ReferenceCounted::release() {
	AssertMessageException(_count > 1);
	--_count;
	if(0 == _count) {
		delete this;
	}
}
inline int32_t ReferenceCounted::references() const {
	return _count;
}
