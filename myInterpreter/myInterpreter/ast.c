#include "ast.h"
#include<string.h>


const char* letTokenLiteral(void* self) {
    LetStatement* ls = (LetStatement*)self; // self�� LetStatement�� ��ȯ
    return ls->token->literal;  // LetStatement�� ���� TokenLiteral ��ȯ
}

const char* identifierTokenLiteral(void* self) {
    Identifier* id = (Identifier*)self; // self�� Identifier�� ��ȯ
    return id->token->literal;  // Identifier�� ���� TokenLiteral ��ȯ
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
// Program �޼��� ���� (���α׷����� ù ��° Statement�� TokenLiteral ȣ��)
const char* programTokenLiteral(void* self) {
    Program* p = (Program*)self;

    if (p->statementsNum > 0) {
        return p->statements[0]->node.TokenLiteral(p->statements[0]);
    }
    return "";
}





// LetStatement �� Identifier ��ü ���� �Լ�
LetStatement* newLetStatement() {
    LetStatement* ls = (LetStatement*)malloc(sizeof(LetStatement));
    // LetStatement�� TokenLiteral �Լ� �����͸� ����
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
    char* str = NULL;
    for (int i = 0; i < len; i++) {
        append_string(&str, p->statements[i]->node.PrintString(p->statements[i]));
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

    if (es->is_valid == 1) {
        return es->expression.node.TokenLiteral(es);
    }
    return "";
}

const char* printIdentifier(void* self)
{
    Identifier* i = (Identifier*)self;

    return i->value;
}
void append_string(char** dest, const char* src) {
    if (!src || !dest) return;  // dest�� NULL�� ��쵵 üũ

    size_t new_len = (*dest ? strlen(*dest) : 0) + strlen(src) + 1;
    char* new_str = (char*)realloc(*dest, new_len);

    if (!new_str) {
        perror("Memory allocation failed");
        exit(1);
    }

    if (*dest == NULL)  // �ʱ� ���¶�� strcpy ���
        strcpy(new_str, src);
    else
        strcat(new_str, src);

    *dest = new_str;
}


