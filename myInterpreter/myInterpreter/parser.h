#pragma once
#include "ast.h"
#include "lexer.h"
#include "token.h"

#define LOWEST 1
#define EQUALS 2
#define LESSGREATER 3
#define SUM 4
#define PRODUCT 5
#define PREFIX 6
#define CALL 7


typedef struct _parser {
	Lexer* l;
	Token* curToken;
	Token* peekToken;

	char** errors;
	int errorsNum;
}Parser;

Parser* NewParser(Lexer* l);
void pNextToken(Parser* p);
Program* ParseProgram(Parser* p); 

Statement* parseStatement(Parser* p);
LetStatement* parseLetStatement(Parser*p);
ReturnStatement* parseReturnStatement(Parser* p);
ExpressionStatement* parseExpressionStatement(Parser* p);
Expression parseExpression(int priority, Parser* p);
bool curTokenIs(Parser* p,TokenType t);
bool peekTokenIs(Parser* p, TokenType t);
bool expectPeek(Parser* p, TokenType t);

const char** Errors(Parser* p);
void peekError(Parser* p, TokenType t);


void freeParser(Parser* p);