#include <stdio.h>
#include <string>
#include <vector>
#include <os/File.h>

// clang++ compiler.cpp -I.. -o /tmp/compiler -Wall -Weffc++ -Wextra -Wshadow -Wwrite-strings

enum TokenType {
	tWhitespace,
	tWord,
	tPunctuation,
	tComment,
	tStringLiteral,
};
const char *typeName(TokenType type) {
	switch(type) {
		case tWhitespace: return "Whitespace";
		case tWord: return "Word";
		case tPunctuation: return "Punctuation";
		case tComment: return "Comment";
		case tStringLiteral: return "String";
		default: break;
	}
	return "[Unknown]";
}
typedef std::vector<std::string>	StringList;
struct Token {
	TokenType				type;
	std::string				value;
	std::string::size_type	position;
	StringList				parts;
	Token(TokenType t, const std::string &v, std::string::size_type p):type(t),value(v),position(p),parts(){
		parts.push_back(value);
	}
};
typedef std::vector<Token>	TokenList;
class TokenException : public msg::Exception {
	public:
		TokenException(const std::string &message, const char *file, int line, int column) throw()
			:msg::Exception(_init(message,column), file, line){}
		virtual ~TokenException() throw() {}
	private:
		std::string _init(const std::string &message, int column) {
			std::stringstream	stream;

			stream << column;
			return message+" at column: "+stream.str();
		}
};
void throwLinePositionException(const std::string &message, const char * const file, const std::string &contents, const std::string::size_type position) {
	int								line= 1;
	std::string::size_type			sol= 0, eol, cr, lf;
	const std::string::size_type	notFound= std::string::npos;

	//printf("[[%s]]\n",contents.c_str());
	while(sol < contents.size()) {
		cr= contents.find('\r',sol);
		lf= contents.find('\n',sol);
		eol= (notFound == cr ? (notFound == lf ? contents.size() : lf) : (lf < cr ? lf : cr));
		if( (eol == cr) && (eol + 1 < contents.size()) ) {
			if('\n' == contents[eol+1]) {
				++eol;
			}
		}
		//printf("line=%d sol=%d cr=%d lf=%d eol=%d\n", line, static_cast<int>(sol), static_cast<int>(cr), static_cast<int>(lf), static_cast<int>(eol));
		if( (sol <= position) && (position <= eol) ) {
			throw TokenException(message, file, line, position - sol);
		}
		sol= eol+1;
		++line;
	}
	throw TokenException(message, file, line, 1);
}
TokenList &combineTokens(TokenList &tokens) {
	for(TokenList::iterator i= tokens.begin(); i != tokens.end(); ++i) {
		if(tWord == i->type) {
			TokenList::iterator	j= i+1;

			if( (j != tokens.end()) && (j->value == ".") ) {
				TokenList::iterator	k= j+1;

				if( (k != tokens.end()) && (tWord == k->type) ) {
					i->parts.push_back(k->value);
					i->value+= j->value+k->value;
					tokens.erase(k);
					tokens.erase(j);
				}
			}
		} else if(tStringLiteral == i->type) {
			TokenList::iterator	j= i+1;

			if( (j != tokens.end()) && (tStringLiteral == j->type) ) {
				i->value+= j->value;
				j->value.erase(0,1);
				i->parts[0]+= j->value;
				tokens.erase(j);
			}
		}
	}
	return tokens;
}
TokenList &tokenize(const std::string &text, const char *filename, TokenList &tokens) {
	const std::string symbolCharacters("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_");
	const std::string punctuationCharacters("[].=;/,");
	const std::string spaceCharacters(" \t\r\n");
	std::string::size_type	start= 0, end;

	tokens.clear();
	while(start < text.size()) {
		if(text[start] == '\\') {
			end= text.find('\r', start);
			if(std::string::npos == end) {
				end= text.find('\n', start);
			}
			if(std::string::npos == end) {
				end= text.size();
			}
			tokens.push_back(Token(tComment,text.substr(start, end-start),start));
			start= end;
		} else if(text[start] == '\'') {
			end= text.find('\'', start+1);
			if(std::string::npos == end) {
				throwLinePositionException("Unterminated String", filename, text, start);
			}
			tokens.push_back(Token(tStringLiteral,text.substr(start, end-start+1),start));
			start= end+1;
		} else if(punctuationCharacters.find(text[start])!=std::string::npos) {
			tokens.push_back(Token(tPunctuation,text.substr(start, 1),start));
			++start;
		} else if(spaceCharacters.find(text[start])!=std::string::npos) {
			end= start+1;
			while( (end < text.size()) && (spaceCharacters.find(text[end])!=std::string::npos) ) {
				++end;
			}
			tokens.push_back(Token(tWhitespace,text.substr(start, end-start),start));
			start= end;
		} else {
			end= start;
			while( (end < text.size()) && (symbolCharacters.find(text[end])!=std::string::npos) ) {
				++end;
			}
			if(start != end) {
				tokens.push_back(Token(tWord,text.substr(start, end-start),start));
				start= end;
			} else {
				throwLinePositionException("Unknown character", filename, text, start);
			}
		}
	}
	return tokens;
}
int main(const int argc, const char *argv[]) {
	for(int arg= 1; arg < argc; ++arg) {
		try {
			io::File	file(argv[arg], io::File::Text, io::File::ReadOnly);
			TokenList	tokens;
			std::string	buffer;

			combineTokens(tokenize(file.read(buffer), argv[arg], tokens));
			for(TokenList::iterator i= tokens.begin(); i != tokens.end(); ++i) {
				printf("%s@%d <<%s>> ", typeName(i->type), static_cast<int>(i->position), i->value.c_str());
				for(StringList::iterator p= i->parts.begin(); p != i->parts.end(); ++p) {
					printf("{{%s}} ", p->c_str());
				}
				printf("\n");
			}
		} catch(const std::exception &exception) {
			printf("EXCEPTION: path='%s' error='%s'\n", argv[arg],exception.what());
		}
	}
	return 0;
}
