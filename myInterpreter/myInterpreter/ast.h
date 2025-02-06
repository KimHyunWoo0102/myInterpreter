#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "token.h"

// Node �������̽��� ���� �Լ� ������ ����
typedef const char* (*TokenLiteralFunc)(void*);
typedef const char* (*PrintStringFunc)(void*);
typedef enum statementType { LET, RETURN ,IDENTIFIER,EXPRESSIONSTMT}StatementType;

typedef struct _node {
    TokenLiteralFunc TokenLiteral;
    PrintStringFunc PrintString;
    StatementType statementType; //���߿� free ��Ű�� ����
}Node;

// Statement, Expression ����ü ���� (Node "���" ����)
typedef struct _statement {
    Node node;
    void (*statementNode)(void*);      // ���� �޼���
} Statement;

typedef struct _expression {
    Node node;      // TokenLiteral �޼���
    void (*expressionNode)(void*);     // ���� �޼���
} Expression;

// Identifier ����ü ����
typedef struct _identifier {
    Token* token;                      // Identifier�� ��ū
    Node node;     
    char* value;                       // Identifier ��
} Identifier;

// LetStatement ����ü ����
typedef struct _letStatement {
    Statement statement;              // Statement ���� (��� ����)
    Token* token;                      // let Ű���� ��ū
    Identifier* name;                  // ���� �̸�
    Expression* value;                 // ���� ��
} LetStatement;

typedef struct _returnStatement {
    Statement statement;
    Token* token;
    Expression* returnValue;
}ReturnStatement;

typedef struct _expressionStatement {
    Expression expression;
    Token* token;
    int is_valid;
}ExpressionStatement;
// Program ����ü ����
typedef struct _program {
    Statement** statements;            // Statement ������ �迭
    int statementsNum;                 // Statement ��
} Program;


const char* identifierTokenLiteral(void* self);
const char* programTokenLiteral(void* self);
const char* returnTokenLiteral(void* self);
const char* expressionTokenLiteral(void* self);
const char* letTokenLiteral(void* self);

LetStatement* newLetStatement();
Identifier* newIdentifier();
ReturnStatement* newReturnStatement();
ExpressionStatement* newExpressionStatement();
Program* newProgram();

const char* printProgram(void* self);
const char* printLetStmt(void*self);
const char* printReturnStmt(void* self);
const char* printExpressionStmt(void* self);
const char* printIdentifier(void* self);