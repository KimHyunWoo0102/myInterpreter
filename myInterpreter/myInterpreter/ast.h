#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "token.h"

// Node �������̽��� ���� �Լ� ������ ����
typedef const char* (*TokenLiteralFunc)(void*);


typedef struct _node {
    TokenLiteralFunc TokenLiteral;
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
    TokenLiteralFunc TokenLiteral;     // TokenLiteral �޼���
    char* value;                       // Identifier ��
} Identifier;

// LetStatement ����ü ����
typedef struct _letStatement {
    Node node;              // Statement ���� (��� ����)
    Token* token;                      // let Ű���� ��ū
    Identifier* name;                  // ���� �̸�
    Expression* value;                 // ���� ��
} LetStatement;

// Program ����ü ����
typedef struct _program {
    Statement** statements;            // Statement ������ �迭
    int statementsNum;                 // Statement ��
} Program;

// �Լ� ����

// LetStatement ���� �Լ�
LetStatement* newLetStatement();
const char* letTokenLiteral(void* self);

// Identifier ���� �Լ�
Identifier* newIdentifier();
const char* identifierTokenLiteral(void* self);

// Program ���� �Լ�
const char* programTokenLiteral(Program* p);
