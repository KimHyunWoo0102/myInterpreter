#pragma once
#include"token.h"
#include<stdbool.h>

typedef struct _lexer {
	char* input;
	int position;//�Է¿��� ���� ��ġ(���� ����)
	int readPosition;//�Է¿��� ���� �д� ��ġ(���� ������ ����)
	char ch;//���� �����ϴ� ����
}Lexer;

Lexer* New(char* input);
void readChar(Lexer* lexer);
char* readNumber(Lexer* lexer);
Token* NextToken(Lexer* lexer);
Token* newToken(TokenType token,char input);

void skipWhitespace(Lexer* l);
bool isLetter(char ch);
bool isDigit(char ch);
char* readIdentifier(Lexer* l);
const char* LookupIdent(const char* ident);