#pragma once


#include <stdlib.h>
#include <string.h>

void freeLexer(Lexer* lexer);
void freeToken(Token* token);
void freeLetStatement(LetStatement* stmt);
void freeIdentifier(Identifier* id);
void freeProgram(Program* program);
void freeStatement(Statement* stmt);
void freeErrors(Parser* p);
void freeParser(Parser* p);
