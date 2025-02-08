#pragma once
#include "ast.h"
#include "lexer.h"
#include "token.h"

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

bool curTokenIs(Parser* p,TokenType t);
bool peekTokenIs(Parser* p, TokenType t);
bool expectPeek(Parser* p, TokenType t);

const char** Errors(Parser* p);
void peekError(Parser* p, TokenType t);


void freeParser(Parser* p);