#pragma once

typedef enum _tokenType{
	ILLEGAL_TOKEN,
	EOF_TOKEN,
	//식별자 + 리터럴
	IDENT_TOKEN,
	INT_TOKEN,

	//연산자
	ASSIGN_TOKEN,
	PLUS_TOKEN,

	//구분자
	COMMA_TOKEN,
	SEMICOLON_TOKEN,

	LPAREN_TOKEN,
	RPAREN_TOKEN,
	LBRACE_TOKEN,
	RBRACE_TOKEN,

	//예약어
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