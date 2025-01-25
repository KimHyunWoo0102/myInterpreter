#pragma once

#define ILLEGAL_TOKEN "ILLEGAL_TOKEN"
#define EOF_TOKEN "EOF"
#define IDENT_TOKEN "IDENT"
#define INT "INT"

// ������
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
// ������
#define COMMA_TOKEN ","
#define SEMICOLON_TOKEN ";"

#define LPAREN_TOKEN "("
#define RPAREN_TOKEN ")"
#define LBRACE_TOKEN "{"
#define RBRACE_TOKEN "}"

// �����
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
	//type�� enum���� ������ �δٰ� ���߿� �ʿ��ϸ� TokenType���� ����ϰ�
	//literal�� ����� Ư���ϰ� �޾ƿ��°� �긦 ��� 5�� ����ǰ� �̰� INT�� ���߿� ��ū Ÿ������ �α�
}Token;
