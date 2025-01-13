#pragma once

typedef enum _tokenType{
	ILLEGAL_TOKEN,
	EOF_TOKEN,
	//�ĺ��� + ���ͷ�
	IDENT_TOKEN,
	INT_TOKEN,

	//������
	ASSIGN_TOKEN,
	PLUS_TOKEN,

	//������
	COMMA_TOKEN,
	SEMICOLON_TOKEN,

	LPAREN_TOKEN,
	RPAREN_TOKEN,
	LBRACE_TOKEN,
	RBRACE_TOKEN,

	//�����
	FUNCTION_TOKEN,
	LET_TOKEN
}TokenType;

static const char* TokenTypeNames[] = {
	"ILLEGAL",
	"EOF",
	"IDENT",
	"INT",
	"=",
	"+",
	",",
	";",
	"(",
	")",
	"{",
	"}",
	"FUNCTION",
	"LET"
};

typedef struct _token {
	TokenType type;
	char* literal;
}Token;