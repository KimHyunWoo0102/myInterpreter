#pragma once
#include"token.h"

typedef struct _lexer {
	char* input;
	int position;//입력에서 현재 위치(현재 문자)
	int readPosition;//입력에서 현재 읽는 위치(현재 문자의 다음)
	char ch;//현재 조사하는 문자
}Lexer;

Lexer* New(char* input);
void readChar(Lexer* lexer);
Token* NextToken(Lexer* lexer);
Token* newToken(TokenType token);