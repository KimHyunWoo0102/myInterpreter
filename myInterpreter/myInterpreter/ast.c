#include "ast.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>


const char* letTokenLiteral(void* self) {
    LetStatement* ls = (LetStatement*)self; // self를 LetStatement로 변환
    return ls->token->literal;  // LetStatement에 대한 TokenLiteral 반환
}

const char* identifierTokenLiteral(void* self) {
    Identifier* id = (Identifier*)self; // self를 Identifier로 변환
    return id->token->literal;  // Identifier에 대한 TokenLiteral 반환
}
const char* returnTokenLiteral(void* self)
{
    ReturnStatement* rs = (ReturnStatement*)self;
    return rs->token->literal;
}
const char* expressionTokenLiteral(void* self)
{
    ExpressionStatement* es = (ExpressionStatement*)self;
    return es->token->literal;
}
// Program 메서드 구현 (프로그램에서 첫 번째 Statement의 TokenLiteral 호출)
const char* programTokenLiteral(void* self) {
    Program* p = (Program*)self;

    if (p->statementsNum > 0) {
        return p->statements[0]->node.TokenLiteral(p->statements[0]);
    }
    return "";
}





// LetStatement 및 Identifier 객체 생성 함수
LetStatement* newLetStatement() {
    LetStatement* ls = (LetStatement*)malloc(sizeof(LetStatement));
    // LetStatement의 TokenLiteral 함수 포인터를 설정
    ls->statement.node.TokenLiteral = letTokenLiteral;
    ls->statement.node.statementType = LET;
    ls->statement.node.PrintString = printLetStmt;

    return ls;
}

Identifier* newIdentifier() {
    Identifier* id = (Identifier*)malloc(sizeof(Identifier));
   
    id->node.TokenLiteral = identifierTokenLiteral;
    id->node.statementType = IDENTIFIER;

    return id;
}

ReturnStatement* newReturnStatement()
{
    ReturnStatement* rs = (ReturnStatement*)malloc(sizeof(ReturnStatement));
    rs->statement.node.TokenLiteral = returnTokenLiteral;
    rs->statement.node.statementType = RETURN;
    rs->statement.node.PrintString = printReturnStmt;
    return rs;
}

ExpressionStatement* newExpressionStatement()
{
    ExpressionStatement* es = (ExpressionStatement*)malloc(sizeof(ExpressionStatement));
    es->expression.node.TokenLiteral = expressionTokenLiteral;
    es->expression.node.statementType = EXPRESSIONSTMT;
    es->is_valid = 1;
    es->expression.node.PrintString = printExpressionStmt;
    return es;
}

Program* newProgram()
{
    Program*p= (Program*)malloc(sizeof(Program));
    p->statements = NULL;
    p->statementsNum = 0;
    
    return p;
}

const char* printProgram(void* self)
{
    Program* p = (Program*)self;

    int len = p->statementsNum;
    char* str = NULL, * tmp = NULL;
    for (int i = 0; i < len; i++) {
        if(tmp==NULL)
            tmp = p->statements[i]->node.PrintString(p->statements[i]);

        append_string(&str, tmp);

        free(tmp);
        tmp = NULL;
    }
    return str;
}

const char* printLetStmt(void* self)
{
    LetStatement* ls = (LetStatement*)self;

    char* str = NULL;
    append_string(&str, ls->statement.node.TokenLiteral(ls));
    append_string(&str, " ");
    append_string(&str, ls->name->node.TokenLiteral(ls->name));
    append_string(&str, " = ");

    if (ls->value != NULL) {
        append_string(&str,ls->value->node.TokenLiteral(ls->value));
    }

    append_string(&str, ";");

    return str;
}

const char* printReturnStmt(void* self)
{
    ReturnStatement* rs = (ReturnStatement*)self;
    char* str = NULL;

    append_string(&str, rs->statement.node.TokenLiteral(rs));
    append_string(&str, " ");

    if (rs->returnValue != NULL) {
        append_string(&str, rs->returnValue->node.TokenLiteral(rs->returnValue));
    }

    append_string(&str, ";");
    return str;
}

const char* printExpressionStmt(void* self)
{
    ExpressionStatement* es = (ExpressionStatement*)self;
    char* str = NULL;
    if (es->is_valid == 1) {
        str = _strdup(es->expression.node.TokenLiteral(es));
        
    }else
        str = _strdup("");
    return str;
}

const char* printIdentifier(void* self)
{
    Identifier* i = (Identifier*)self;
    char* str = _strdup(i->value);
    return str;
}
void freeProgram(Program* p)
{
    for (int i = 0; i < p->statementsNum; i++) {
        int type = p->statements[i]->node.statementType;
        switch (type)
        {
        case LET:
            freeLetStmt((LetStatement*)p->statements[i]);
            break;
        case RETURN:
            break;
        case IDENTIFIER:
            break;
        case EXPRESSIONSTMT:
            break;

        }
    }

    free(p->statements);
    free(p);
}
void freeLetStmt(LetStatement* ls)
{
    freeToken(ls->token);

    if (ls->name != NULL)
        freeIdentifier(ls->name);

    if (ls->value != NULL && ls->value->node.statementType == EXPRESSIONSTMT)
        freeExpressionStmt(ls->value);
    else if (ls->value != NULL && ls->value->node.statementType == IDENTIFIER)
        freeIdentifier(ls->value);

    free(ls);
}
void freeIdentifier(Identifier* i)
{
    freeToken(i->token);
    free(i);
}
void freeExpressionStmt(ExpressionStatement* es)
{
    free(es->token);
    free(es);
}
void append_string(char** dest, const char* src) {
    if (!src || !dest) return;  // src 또는 dest가 NULL인지 확인

    size_t old_len = (*dest ? strlen(*dest) : 0);
    size_t src_len = strlen(src);
    size_t new_len = old_len + src_len + 1;  // 널 종료 문자 포함

    char* new_str = (char*)realloc(*dest, new_len);
    if (!new_str) {
        perror("Memory allocation failed");
        exit(1);
    }

    if (old_len == 0) {
        // 기존 문자열이 없을 경우 strcpy_s 사용
        if (strcpy_s(new_str, new_len, src) != 0) {
            perror("strcpy_s failed");
            exit(1);
        }
    }
    else {
        // 기존 문자열이 있을 경우 strcat_s 사용
        if (strcat_s(new_str, new_len, src) != 0) {
            perror("strcat_s failed");
            exit(1);
        }
    }

    *dest = new_str;
}


