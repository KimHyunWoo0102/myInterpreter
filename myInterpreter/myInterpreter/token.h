#pragma once

#define ILLEGAL_TOKEN "ILLEGAL_TOKEN"
#define EOF_TOKEN "EOF"
#define IDENT_TOKEN "IDENT"
#define INT "INT"

// 연산자
#define ASSIGN_TOKEN "="
#define PLUS_TOKEN "+"
#define MINUS_TOKEN "-"
#define BANG_TOKEN "!"
#define ASTERISK_TOKEN "*"
#define SLASH_TOKEN "/"

#define LT_TOKEN "<"
#define GT_TOKEN ">"

#define EQ_TOKEN "=="
#define NOT_EQ_TOKEN "!="
// 구분자
#define COMMA_TOKEN ","
#define SEMICOLON_TOKEN ";"

#define LPAREN_TOKEN "("
#define RPAREN_TOKEN ")"
#define LBRACE_TOKEN "{"
#define RBRACE_TOKEN "}"

// 예약어
#define FUNCTION_TOKEN "FUNCTION"
#define LET_TOKEN "LET"
#define TRUE_TOKEN "TRUE"
#define FALSE_TOKEN "FALSE"
#define IF_TOKEN "IF"
#define ELSE_TOKEN "ELSE"
#define RETURN_TOKEN "RETURN"

typedef const char* TokenType;

typedef struct _token {
	TokenType type;
	char* literal;
	//type은 enum으로 저장해 두다가 나중에 필요하면 TokenType으로 사용하고
	//literal은 어떤건지 특정하게 받아오는것 얘를 들어 5가 저장되고 이걸 INT로 나중에 토큰 타입으로 두기
}Token;
