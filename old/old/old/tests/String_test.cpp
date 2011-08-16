#include "ReferencedBuffer.h"
#include "ASCIIBufferString.h"
#include "JoinString.h"
#include "SubString.h"
#include <string>

// g++ -c -o /tmp/String.o String.cpp -I.. -g -Wall -Weffc++ -Wextra -Wshadow -Wwrite-strings
// g++ -c -o /tmp/String_test.o tests/String_test.cpp -I.. -g -Wall -Weffc++ -Wextra -Wshadow -Wwrite-strings
// g++ -o /tmp/test /tmp/String_test.o /tmp/String.o
// /tmp/test

#define FullSentence "Testing the search, join and substring facilities of the Strings. Also testing buffers through this."

int main(int argc, const char *argc[]) {
	StringPtr	fullSentence= ASCIIBufferString::create(ReferencedBuffer::create(FullSentence, strlen(FullSentence)));
	
	return 0;
}
