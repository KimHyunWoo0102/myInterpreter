#include "parser.h"
#include <stdio.h>
#include<stdlib.h>

Parser* NewParser(Lexer* l)
{
    Parser* parser = (Parser*)malloc(sizeof(Parser));  // Parser 메모리 할당
    parser->l = l;  // Parser의 l 필드를 주어진 Lexer 포인터로 초기화
   
    pNextToken(parser);
    pNextToken(parser);//토큰 세팅

    return parser;
}

void pNextToken(Parser* p)
{
    p->curToken = p->peekToken;
    p->peekToken = NextToken(p->l);
}

Program* ParseProgram(Parser* p)
{
    Program* program = (Program*)malloc(sizeof(Program));
    program->statements = NULL;
    program->statementsNum = 0;
    //프로그램 만든후(statements 저장할 구조체) 초기화


    //모든 줄을 다 읽을때까지 반복
    while (p->curToken->type != EOF_TOKEN) {
        Statement *stmt = parseStatement(p);
        if (stmt != NULL) {
            program->statementsNum++;
            program->statements = (Statement**)realloc(program->statements, sizeof(Statement*) * program->statementsNum);
            program->statements[program->statementsNum - 1] = stmt;
        }

        pNextToken(p);
    }
    return program;
}

Statement* parseStatement(Parser* p) {
    const char* type = p->curToken->type;

    if (strcmp(type, LET_TOKEN) == 0)
        return (Statement*)parseLetStatement(p);
    return NULL;
}

LetStatement* parseLetStatement(Parser* p) {
    LetStatement *stmt = newLetStatement();
    stmt->token = p->curToken;
    //stmt->token에 LET 토큰 저장

    if (!expectPeek(p, IDENT_TOKEN)) {
        return NULL;
    }//LET 이후 변수명이 나오는지 검사

    stmt->name = newIdentifier();
    //name은 변수명을 의미함 변수명에 현재 어떤 토큰인지 
    stmt->name->token = p->curToken;
    stmt->name->value = p->curToken->literal;
    
    if (!expectPeek(p, ASSIGN_TOKEN)) {
        return NULL;
    }//만약 다음이 = 인지 검사

    //TODO: 세미콜론을 만날때까지 건너뜀

    while (!curTokenIs(p, SEMICOLON_TOKEN)) {
        pNextToken(p);
    }//세미 콜론까지 일단 제낌


    //test로 Let x = 10;이 들어온다면 현재 Let과 x만 저장되고 뒷부분은 날림
    return stmt;
}

bool curTokenIs(Parser* p, TokenType t)
{
    return p->curToken->type==t;
}

bool peekTokenIs(Parser* p, TokenType t)
{
    return p->peekToken->type==t;
}

bool expectPeek(Parser* p, TokenType t)
{
    if (peekTokenIs(p,t)) {
        pNextToken(p);
        return true;
    }
    return false;
}

