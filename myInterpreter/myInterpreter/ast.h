#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "token.h"

// Node 인터페이스를 위한 함수 포인터 정의
typedef const char* (*TokenLiteralFunc)(void*);
typedef enum statementType { LET, RETURN ,IDENTIFIER}StatementType;

typedef struct _node {
    TokenLiteralFunc TokenLiteral;
    StatementType statementType; //나중에 free 시키기 위함
}Node;

// Statement, Expression 구조체 정의 (Node "상속" 역할)
typedef struct _statement {
    Node node;
    void (*statementNode)(void*);      // 더미 메서드
} Statement;

typedef struct _expression {
    Node node;      // TokenLiteral 메서드
    void (*expressionNode)(void*);     // 더미 메서드
} Expression;

// Identifier 구조체 정의
typedef struct _identifier {
    Token* token;                      // Identifier의 토큰
    Node node;     
    char* value;                       // Identifier 값
} Identifier;

// LetStatement 구조체 정의
typedef struct _letStatement {
    Node node;              // Statement 포함 (상속 역할)
    Token* token;                      // let 키워드 토큰
    Identifier* name;                  // 변수 이름
    Expression* value;                 // 변수 값
} LetStatement;

typedef struct _returnStatement {
    Node node;
    Token* token;
    Expression* returnValue;
}ReturnStatement;
// Program 구조체 정의
typedef struct _program {
    Statement** statements;            // Statement 포인터 배열
    int statementsNum;                 // Statement 수
} Program;


const char* identifierTokenLiteral(void* self);
const char* programTokenLiteral(Program* p);
const char* returnTokenLiteral(void* self);


const char* letTokenLiteral(void* self);

LetStatement* newLetStatement();
Identifier* newIdentifier();
ReturnStatement* newReturnStatement();