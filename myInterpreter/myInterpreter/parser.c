#include "parser.h"
#include <stdio.h>
#include<stdlib.h>

Parser* NewParser(Lexer* l)
{
    Parser* parser = (Parser*)malloc(sizeof(Parser));  // Parser �޸� �Ҵ�
    parser->l = l;  // Parser�� l �ʵ带 �־��� Lexer �����ͷ� �ʱ�ȭ
    parser->errorsNum = 0;
    parser->curToken = NULL;
    parser->peekToken = NULL;
    pNextToken(parser);
    pNextToken(parser);//��ū ����

    return parser;
}

void pNextToken(Parser* p)
{
    //curToken�� �ᱹ stmt�鿡 ���� ����
    p->curToken = p->peekToken;
    p->peekToken = NextToken(p->l);
}

Program* ParseProgram(Parser* p)
{
    Program* program = newProgram();
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
    if (strcmp(type, RETURN_TOKEN) == 0)
        return (Statement*)parseReturnStatement(p);

    return (Statement*)parseExpressionStatement(p);
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

ReturnStatement* parseReturnStatement(Parser* p)
{
    ReturnStatement* stmt = newReturnStatement();
    stmt->token = p->curToken;

    pNextToken(p);

    while (!curTokenIs(p, SEMICOLON_TOKEN)) {
        pNextToken(p);
    }

    return stmt;
}

ExpressionStatement* parseExpressionStatement(Parser* p) {
    ExpressionStatement* stmt = newExpressionStatement();
    stmt->token = p->curToken;
    stmt->expression = parserExpression(LOWEST,p);

    if (!peekTokenis(p, SEMICOLON_TOKEN)) {
        pNextToken(p);
    }

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
    peekError(p, t);
    return false;
}

const char** Errors(Parser* p)
{
    return p->errors;
}

void peekError(Parser* p, TokenType t)
{
    const char* format = "expected next token to be %s, got %s instead";

    int size = snprintf(NULL, 0, format, t, p->peekToken->type) + 1;  // �ʿ��� ũ�� ���
    char* error = (char*)malloc(size);

    if (error == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    snprintf(error, size, format, t, p->peekToken->type);

    if (error) {
        printf("%s\n", error);  // ���: expected next token to be LET, got INT instead
        free(error);  // ���� �Ҵ� ����
        return;
    }

    p->errorsNum++;
    p->errors = (char**)realloc(p->errors, sizeof(char*) * p->errorsNum);
    if (p->errors == NULL) {
        // �޸� �Ҵ� ���� ó��
        printf("Memory allocation failed!\n");
    }
    else {
        p->errors[p->errorsNum - 1] = error;
        // �޸� �Ҵ� ���� �� ������Ʈ
    }
}

void freeParser(Parser* p)
{
    if(p->l!=NULL)
        freeLexer(p->l);

    for (int i = 0; i < p->errorsNum; i++) {
        free(p->errors[i]);
    }

    free(p->errors);
}

