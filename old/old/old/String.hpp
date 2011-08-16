inline StringPtr String::trimFromStart(size_t count) {
	return substring(0, count);
}
inline StringPtr String::trimFromEnd(size_t count) {
	const size_t	myLength= length();
	
	AssertMessageException(myLength >= count);
	return substring(myLength - count);
}
inline StringPtr operator+(StringParam s1, StringParam s2) {
	return s1->append(s2);
}
