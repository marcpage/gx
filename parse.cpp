#include <string>
#include <stdio.h>
#include <vector>
#include <ctype.h>

enum TokenType {
	TokenSpace,
	TokenNumber,
	TokenName,
	TokenDot,
	TokenStartGroup,
	TokenEndGroup,
	TokenCode,
	TokenText,
	TokenEnd,
	TokenOther,
};

struct Token {TokenType type; std::string contents;};
typedef std::vector<Token>					TokenList;
typedef int (*CharType)(int);

struct IsSpace {bool operator()(char value) {return isspace(value);} TokenType type() {return TokenSpace;}};
struct IsDigit {bool operator()(char value) {return isdigit(value);} TokenType type() {return TokenNumber;}};
struct IsAlnum {bool operator()(char value) {return isalnum(value);} TokenType type() {return TokenName;}};

template<typename F>
bool parse(const std::string &contents, std::string::size_type &position, Token &token) {
	std::string::size_type	index= position;

	while(F()(contents[index])) {
		++index;
	}
	if( index > position ) {
		token.type= F().type();
		token.contents.assign(contents, position, index - position);
		position= index;
		return true;
	}
	return false;
}
bool parseText(const std::string &contents, std::string::size_type &position, Token &token) {
	std::string::size_type	index= position;

	if(contents[index] == '\'') {
		++index;
		while(contents[index] != '\'') {
			if(contents[index] == '\\') {
				++index;
			}
			++index;
		}
		++index;
		token.type= TokenText;
		token.contents.assign(contents, position, index - position);
		position= index;
		return true;
	}
	return false;
}

void tokenize(const std::string &contents, TokenList &tokens) {
	std::string::size_type	start= 0;
	Token					token;

	tokens.clear();
	while(start < contents.size()) {
		if(parse<IsSpace>(contents, start, token)) {
			tokens.push_back(token);
		} else if(parse<IsDigit>(contents, start, token)) {
			tokens.push_back(token);
		} else if(parse<IsAlnum>(contents, start, token)) {
			tokens.push_back(token);
		} else if(parseText(contents, start, token)) {
			tokens.push_back(token);
		} else switch(contents[start]) {
			case '.': token.type= TokenDot; token.contents.assign(1, '.'); ++start; tokens.push_back(token); break;
			case '[': token.type= TokenStartGroup; token.contents.assign(1, '['); ++start; tokens.push_back(token); break;
			case ']': token.type= TokenEndGroup; token.contents.assign(1, ']'); ++start; tokens.push_back(token); break;
			case '/': token.type= TokenCode; token.contents.assign(1, '/'); ++start; tokens.push_back(token); break;
			case ';': token.type= TokenEnd; token.contents.assign(1, ';'); ++start; tokens.push_back(token); break;
			default: token.type= TokenOther; token.contents.assign(1, contents[start]); ++start; tokens.push_back(token); break;
		}
	}
}

void read(const std::string &path, std::string &contents) {
	FILE	*f= fopen(path.c_str(), "r");
	off_t	size;

	fseek(f, 0, SEEK_END);
	size= ftello(f);
	fseek(f, 0, SEEK_SET);
	contents.assign(size, '\0');
	fread(const_cast<char*>(contents.data()), 1, size, f);
	fclose(f);
}

int main(int argc, const char * const argv []) {
	std::string	contents;
	TokenList	tokens;

	for(int arg= 1; arg < argc; ++arg) {
		read(argv[arg], contents);
		tokenize(contents, tokens);
		printf("--%s--\n",argv[arg]);
		for(TokenList::iterator token= tokens.begin(); token != tokens.end(); ++token) {
			printf("\t%d - '%s'\n", token->type, token->contents.c_str());
		}
	}
	return 0;
}
