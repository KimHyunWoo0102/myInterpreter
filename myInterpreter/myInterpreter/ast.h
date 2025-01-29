#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "token.h"

// Node �������̽��� ���� �Լ� ������ ����
typedef const char* (*TokenLiteralFunc)(void*);
typedef enum statementType { LET, RETURN ,IDENTIFIER}StatementType;

typedef struct _node {
    TokenLiteralFunc TokenLiteral;
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
    Node node;              // Statement ���� (��� ����)
    Token* token;                      // let Ű���� ��ū
    Identifier* name;                  // ���� �̸�
    Expression* value;                 // ���� ��
} LetStatement;

typedef struct _returnStatement {
    Node node;
    Token* token;
    Expression* returnValue;
}ReturnStatement;
// Program ����ü ����
typedef struct _program {
    Statement** statements;            // Statement ������ �迭
    int statementsNum;                 // Statement ��
} Program;


const char* identifierTokenLiteral(void* self);
const char* programTokenLiteral(Program* p);
const char* returnTokenLiteral(void* self);


const char* letTokenLiteral(void* self);

LetStatement* newLetStatement();
Identifier* newIdentifier();
ReturnStatement* newReturnStatement();