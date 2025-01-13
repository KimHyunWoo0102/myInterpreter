#pragma once
#include"token.h"

typedef struct _lexer {
	char* input;
	int position;//�Է¿��� ���� ��ġ(���� ����)
	int readPosition;//�Է¿��� ���� �д� ��ġ(���� ������ ����)
	char ch;//���� �����ϴ� ����
}Lexer;

Lexer* New(char* input);
void readChar(Lexer* lexer);
Token* NextToken(Lexer* lexer);
Token* newToken(TokenType token);