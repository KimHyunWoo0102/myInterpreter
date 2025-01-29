#include "parser.h"
#include <stdio.h>
#include<stdlib.h>

Parser* NewParser(Lexer* l)
{
    Parser* parser = (Parser*)malloc(sizeof(Parser));  // Parser �޸� �Ҵ�
    parser->l = l;  // Parser�� l �ʵ带 �־��� Lexer �����ͷ� �ʱ�ȭ
   
    pNextToken(parser);
    pNextToken(parser);//��ū ����

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
    //���α׷� ������(statements ������ ����ü) �ʱ�ȭ


    //��� ���� �� ���������� �ݺ�
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
    //stmt->token�� LET ��ū ����

    if (!expectPeek(p, IDENT_TOKEN)) {
        return NULL;
    }//LET ���� �������� �������� �˻�

    stmt->name = newIdentifier();
    //name�� �������� �ǹ��� ������ ���� � ��ū���� 
    stmt->name->token = p->curToken;
    stmt->name->value = p->curToken->literal;
    
    if (!expectPeek(p, ASSIGN_TOKEN)) {
        return NULL;
    }//���� ������ = ���� �˻�

    //TODO: �����ݷ��� ���������� �ǳʶ�

    while (!curTokenIs(p, SEMICOLON_TOKEN)) {
        pNextToken(p);
    }//���� �ݷб��� �ϴ� ����


    //test�� Let x = 10;�� ���´ٸ� ���� Let�� x�� ����ǰ� �޺κ��� ����
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

