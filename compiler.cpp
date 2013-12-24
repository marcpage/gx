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
	tBlock,
};
const char *typeName(TokenType type) {
	switch(type) {
		case tWhitespace: return "Whitespace";
		case tWord: return "Word";
		case tPunctuation: return "Punctuation";
		case tComment: return "Comment";
		case tStringLiteral: return "String";
		case tBlock: return "Block";
		default: break;
	}
	return "[Unknown]";
}
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
struct Token;
typedef std::vector<std::string>	StringList;
typedef std::vector<Token>			TokenList;
struct Token {
	TokenType				type;
	std::string				value;
	StringList				parts;
	TokenList				sub;
	const char				*filename;
	int						line, column;
	Token(const Token &token)
		:type(token.type),value(token.value),parts(token.parts),sub(token.sub),filename(token.filename),line(token.line),column(token.column){}
	Token &operator=(const Token &token) {
		type= token.type;
		value= token.value;
		parts= token.parts;
		sub= token.sub;
		filename= token.filename;
		line= token.line;
		column= token.column;
		return *this;
	}
	void failure(const std::string &message) {
		throw TokenException(message, filename, line, column);
	}
	Token(TokenType t, const char *f, const std::string &contents, std::string::size_type position, std::string::size_type count, int &lineAfter, int &columnAfter)
			:type(t),value(contents.substr(position,count)),parts(),sub(),filename(f),line(lineAfter),column(columnAfter) {
		parts.push_back(value);
		std::string::size_type			sol=position - column + 1, eol, cr, lf;
		const std::string::size_type	notFound= std::string::npos;

		while(sol < contents.size()) {
			cr= contents.find('\r',sol);
			lf= contents.find('\n',sol);
			eol= (notFound == cr ? (notFound == lf ? contents.size() : lf) : (lf < cr ? lf : cr));
			if( (eol == cr) && (eol + 1 < contents.size()) ) {
				if('\n' == contents[eol+1]) {
					++eol;
				}
			}
			//printf("sol=%d position=%d eol=%d\n", sol, position, eol);
			if( (sol <= position+count) && (position+count <= eol) ) {
				columnAfter= position + count - sol + 1;
				//printf("columnAfter= %d position=%d count=%d sol=%d\n", columnAfter, position, count, sol);
				return;
			}
			sol= eol+1;
			++lineAfter;
		}
		columnAfter= contents.size() - sol + 1;
		//printf("columnAfter= %d contents.size()=%d sol=%d\n", columnAfter, contents.size(), sol);
	}
};
void formSubToken(TokenList::iterator &i, TokenList &tokens) {
	TokenList::iterator	j= i+1;

	while( (j != tokens.end()) && ("]" != j->value) ) {
		if("[" == j->value) {
			formSubToken(j, tokens);
		}
		i->value+=j->value;
		i->sub.push_back(*j);
		tokens.erase(j);
		j= i+1;
	}
	if(j == tokens.end()) {
		i->failure("Missing end bracket (])");
	}
	i->value+= j->value;
	i->type= tBlock;
	tokens.erase(j);
}
TokenList &formSubTokens(TokenList &tokens) {
	for(TokenList::iterator i= tokens.begin(); i != tokens.end(); ++i) {
		if("[" == i->value) {
			formSubToken(i, tokens);
		}
	}
	return tokens;
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
	const std::string 		symbolCharacters("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_");
	const std::string 		punctuationCharacters("[].=;/,");
	const std::string 		spaceCharacters(" \t\r\n");
	std::string::size_type	start= 0, end;
	int						lineNumber= 1, columnNumber= 1;

	tokens.clear();
	while(start < text.size()) {
		//printf("LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
		if(text[start] == '\\') {
			end= text.find('\r', start);
			if(std::string::npos == end) {
				end= text.find('\n', start);
			}
			if(std::string::npos == end) {
				end= text.size();
			}
			//printf("\t>COMMENT: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
			tokens.push_back(Token(tComment,filename, text, start, end-start, lineNumber, columnNumber));
			//printf("\t<COMMENT: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
			start= end;
		} else if(text[start] == '\'') {
			end= text.find('\'', start+1);
			if(std::string::npos == end) {
				//printf("\t>STRING ERROR: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
				Token(tStringLiteral,filename, text, start, start+1, lineNumber, columnNumber).failure("Unterminated String");
				//printf("\t<STRING ERROR: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
			}
			//printf("\t>STRING: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
			tokens.push_back(Token(tStringLiteral,filename, text, start, end-start+1, lineNumber, columnNumber));
			//printf("\t<STRING: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
			start= end+1;
		} else if(punctuationCharacters.find(text[start])!=std::string::npos) {
			//printf("\t>PUNCTUATION: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
			tokens.push_back(Token(tPunctuation,filename, text, start, 1, lineNumber, columnNumber));
			//printf("\t<PUNCTUATION: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
			++start;
		} else if(spaceCharacters.find(text[start])!=std::string::npos) {
			end= start+1;
			while( (end < text.size()) && (spaceCharacters.find(text[end])!=std::string::npos) ) {
				++end;
			}
			//printf("\t>WHITESPACE: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
			tokens.push_back(Token(tWhitespace,filename, text, start, end-start, lineNumber, columnNumber));
			//printf("\t<WHITESPACE: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
			start= end;
		} else {
			end= start;
			while( (end < text.size()) && (symbolCharacters.find(text[end])!=std::string::npos) ) {
				++end;
			}
			if(start != end) {
				//printf("\t>WORD: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
				tokens.push_back(Token(tWord,filename, text, start, end-start, lineNumber, columnNumber));
				//printf("\t<WORD: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
				start= end;
			} else {
				//printf("\t>UNKNOWN ERROR: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
				Token(tPunctuation,filename, text, start, 1, lineNumber, columnNumber).failure("Unknown character");
				//printf("\t<UNKNOWN ERROR: LINE=%d COLUMN=%d\n", lineNumber, columnNumber);
			}
		}
	}
	return tokens;
}
void printTokens(TokenList &tokens, const std::string &indent="") {
	for(TokenList::iterator i= tokens.begin(); i != tokens.end(); ++i) {
		printf("%s%s@%d:%d <<%s>> ", indent.c_str(), typeName(i->type), i->line, i->column, i->value.c_str());
		for(StringList::iterator p= i->parts.begin(); p != i->parts.end(); ++p) {
			printf("{{%s}} ", p->c_str());
		}
		printf("\n");
		printTokens(i->sub, indent+"\t");
	}
}
int main(const int argc, const char *argv[]) {
	for(int arg= 1; arg < argc; ++arg) {
		try {
			io::File	file(argv[arg], io::File::Text, io::File::ReadOnly);
			TokenList	tokens;
			std::string	buffer;

			formSubTokens(combineTokens(tokenize(file.read(buffer), argv[arg], tokens)));
			printTokens(tokens);
		} catch(const std::exception &exception) {
			fprintf(stderr, "EXCEPTION: path='%s' error='%s'\n", argv[arg],exception.what());
			return 1;
		}
	}
	return 0;
}
