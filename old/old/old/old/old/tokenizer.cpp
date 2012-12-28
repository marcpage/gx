#include <string>
#include <vector>
#include <ctype.h>
#include "posix/File.h"

// g++ -o /tmp/test tokenizer.cpp -I.. -g -Wall -Weffc++ -Wextra -Wshadow -Wwrite-strings
// /tmp/test

std::string &nextToken(const std::string &text, std::string &token, std::string::size_type &offset) {
	const std::string	kNonAlphaNumericTokens(",.;[]=-");
	
	while( (offset < text.size()) && isspace(text[offset]) ) {
		++offset;
	}
	if(offset == text.size()) {
		token.clear();
	} else {
		if(text[offset] == '\'') {
			const std::string::size_type	start= offset;
			
			do	{
				++offset;
			} while( (offset < text.size()) && (text[offset] != '\'') );
			if(offset < text.size()) {
				++offset;
			}
			token.assign(text, start, offset - start);
		} else if( (text[offset] == '/')
				&& (offset + 1 < text.size())
				&& (text[offset + 1] == '/')
				&& (offset + 2 < text.size())
				&& (text[offset + 2] == '/') ) {
			const std::string::size_type	start= offset;
			
			offset+= 3; // skip begin comment marker
			while( (offset + 2 < text.size())
				&& (
					(text[offset] != '/')
					|| (text[offset + 1] != '/')
					|| (text[offset + 2] != '/')
					) ) {
				++offset;
			}
			offset+= 3;
			if(offset > text.size()) {
				offset= text.size();
			}
			token.assign(text, start, offset - start);
		} else if( (text[offset] == '/')
				&& (offset + 1 < text.size())
				&& (text[offset + 1] == '/') ) {
			const std::string::size_type	start= offset;
			
			while( (offset < text.size()) && (text[offset] != '\r') && (text[offset] != '\n') ) {
				++offset;
			}
			token.assign(text, start, offset - start);
		} else if(kNonAlphaNumericTokens.find(text[offset]) != std::string::npos) {
			token.assign(1, text[offset]);
			++offset;
		} else {
			const std::string::size_type	start= offset;
			
			while( (offset < text.size())
					&& !isspace(text[offset])
					&& (kNonAlphaNumericTokens.find(text[offset]) == std::string::npos) ) {
				++offset;
			}
			token.assign(text, start, offset - start);
		}
	}
	return token;
}

bool isComment(const std::string &token) {
	return (token.size() >= 2) && (token[0] == '/') && (token[1] == '/');
}

int nextStatement(const std::string &text, std::vector<std::string> &statement, std::string::size_type &offset) {
	std::string	token;
	
	statement.clear();
	do	{
		nextToken(text, token, offset);
		if(!isComment(token)) {
			statement.push_back(token);
		}
	} while( (offset < text.size()) && (token != ";") );
	if(statement.size() == 1) {
		return -1;
	}
	if( (statement.size() > 2) && (statement[1] == "is") ) {
		return 0; // type declaration
	}
	for(std::vector<std::string>::iterator i= statement.begin(); i != statement.end(); ++i) {
		if(*i == ".") {
			return 2; // invocation
		}
	}
	return 1; // prototype
}

void normalizeNumbersInStatement(std::vector<std::string> &statement) {
	std::vector<std::string>::size_type	tokenIndex= 0;
	
	// merge real parts
	while(tokenIndex + 2 < statement.size()) {
		if( (statement[tokenIndex].size() > 0)
				&& isdigit(statement[tokenIndex][0])
				&& ( (statement[tokenIndex + 1] == "-") || (statement[tokenIndex + 1] == ".") )
				&& (statement[tokenIndex + 2].size() > 0)
				&& isdigit(statement[tokenIndex + 2][0]) ) {
			statement[tokenIndex]+= statement[tokenIndex + 1];
			statement[tokenIndex]+= statement[tokenIndex + 2];
			statement.erase(statement.begin() + tokenIndex + 2);
			statement.erase(statement.begin() + tokenIndex + 1);
		} else {
			++tokenIndex;
		}
	}
	// merge negatives to numbers
	tokenIndex= 0;
	while(tokenIndex + 1 < statement.size()) {
		if( (statement[tokenIndex] == "-")
				&& (statement[tokenIndex + 1].size() > 0)
				&& isdigit(statement[tokenIndex + 1][0]) ) {
			statement[tokenIndex]+= statement[tokenIndex + 1];
			statement.erase(statement.begin() + tokenIndex + 1);
		} else {
			++tokenIndex;
		}
	}
/*
23403 // integer
0x543534 // hex integer
0o5435343 // octal integer
0b101010100 // binary integer
234.43243e-44 // real
2.3e-4i4.5e-6 // complex
*/
}

int main(int argc, const char *argv[]) {
	for(int arg= 1; arg < argc; ++arg) {
		try {
			io::File					file(argv[arg], io::File::Text, io::File::ReadOnly);
			std::string					contents;
			std::string					token;
			std::string::size_type		offset= 0;
			std::vector<std::string>	statement;
			
			file.read(contents);
			do	{
				switch(nextStatement(contents, statement, offset)) {
					case -1: printf("Empty Statement\n"); break;
					case 0: printf("New Type\n"); break;
					case 1: printf("New Method\n"); break;
					case 2: printf("New Call\n"); break;
					default: printf("Unknown\n"); break;
				}
				normalizeNumbersInStatement(statement);
				for(std::vector<std::string>::iterator i= statement.begin(); i != statement.end(); ++i) {
					printf("<<%s>> ", i->c_str());
				}
				printf("\n");
			} while(offset < contents.size());
			nextToken(contents, token, offset);
			while(token.size() > 0) {
				printf("%s\n", token.c_str());
				nextToken(contents, token, offset);
			}
		} catch(const std::exception &exception) {
			printf("ERROR: in %s: %s\n", argv[arg], exception.what());
		}
		
	}
	return 0;
}
