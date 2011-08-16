#include "File.h"
#include "EString.h"
#include <string>
#include <vector>
#include <ctype.h>

// g++ -o /tmp/test parse.cpp -I../posix -g -Wall -Weffc++ -Wextra -Wshadow -Wwrite-strings

/*
(name) is a(n) (type or interface) (behavior)
in terms of (parent) (pseudo) (,) (and) ...
that
acts like a(n) (interface) (,) (and) ...
has a(n) (interface) (name) (,) (and) ...
.
*/

typedef std::vector<EString>	TokenList;

void skipWhitespace(EString &left) {
	while((left.size() > 0) && isspace(left[0])) {
		left.trimFromStart(1);
	}
}

bool parseStringLiteral(EString &left, TokenList &tokens) {
	if('\'' == left[0]) {
		size_t	endQuote= left.find('\'', 1);
		
		AssertMessageException(endQuote != EString::npos);
		tokens.push_back(EString(left, 0, endQuote + 1));
		left.trimFromStart(endQuote + 1);
		return true;
	}
	return false;
}

bool parseNumeric(EString &left, TokenList &tokens) {
	if(isdigit(left[0])) {
		size_t	position;
		
		for(position= 0; isdigit(left[position]) || (left[position] == '.'); ++position) {
		}
		if( (position > 0) && (left[position - 1] == '.') ) {
			--position;
		}
		tokens.push_back(EString(left, 0, position));
		left.trimFromStart(position);
		return true;
	}
	return false;
}

bool parsePunctuation(EString &left, TokenList &tokens) {
	if(ispunct(left[0])) {
		tokens.push_back(EString(left, 0, 1));
		left.trimFromStart(1);
		return true;
	}
	return false;
}

bool parseWord(EString &left, TokenList &tokens) {
	size_t	position;
	
	for(position= 0; isgraph(left[position]) && !ispunct(left[position]); ++position) {
	}
	if(position > 0) {
		tokens.push_back(EString(left, 0, position));
		left.trimFromStart(position);
		return true;
	}
	return false;
}

void parse(const EString &file, TokenList &tokens) {
	EString	left(file);
	
	while(left.size() > 0) {
		skipWhitespace(left);
		
		if(left.size() == 0) {
		} else if(parseStringLiteral(left, tokens)) {
		} else if(parsePunctuation(left, tokens)) {
		} else if(parseNumeric(left, tokens)) {
		} else if(parseWord(left, tokens)) {
		} else {
			ThrowMessageException(std::string("Invalid character: ")+std::string(&file[0], 0, 1));
		}
	}
}

int main(int argc, char *argv[]) {
	if(argc == 2) {
		io::File	file(argv[1], io::File::Text, io::File::ReadOnly);
		std::string	contents;
		TokenList	tokens;
		
		file.read(contents);
		parse(EString(contents.data(), contents.size()), tokens);
		
		for(TokenList::iterator i= tokens.begin(); i != tokens.end(); ++i) {
			printf("%s\n", std::string(&(*i)[0], i->size()).c_str());
		}
	} else {
		printf("argc=%d\n", argc);
	}
	return 0;
}
