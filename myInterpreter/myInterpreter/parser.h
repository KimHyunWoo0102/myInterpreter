#pragma once
#include "ast.h"
#include "lexer.h"
#include "token.h"

typedef struct _parser {
	Lexer* l;
	Token* curToken;
	Token* peekToken;
}Parser;

Parser* NewParser(Lexer* l);
void pNextToken(Parser* p);
Program* ParseProgram(Parser* p); 
Statement* parseStatement(Parser* p);
LetStatement* parseLetStatement(Parser*p);
bool curTokenIs(Parser* p,TokenType t);
bool peekTokenIs(Parser* p, TokenType t);
bool expectPeek(Parser* p, TokenType t);

