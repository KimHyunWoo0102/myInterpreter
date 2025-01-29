#include "parser_test.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void checkParserErrors(Parser* p) {
    const char** errors = Errors(p);

    if (p->errorsNum == 0) {
        return;
    }

    printf("parser has %d errors\n", p->errorsNum);

    for (int i = 0; i < p->errorsNum; i++) {
        printf("parser error: %s\n", errors[i]);
    }
}

void TestLetStatement()
{
    const char* input =
        "let x  5;"
        "let  = 10;"
        "let 838383;";

    Lexer* l = NewLexer(input);
    Parser* p = NewParser(l); // ������ ������ �ļ� ����

    Program* program = ParseProgram(p); // �Ľ̵� ����� ���α׷� AST�� ����
    checkParserErrors(p);
    if (program == NULL) {
        printf("ParseProgram() returned NULL!\n");
        return;
    }

    if (program->statementsNum != 3) {
        printf("Statements do not contain 3 statements. got = %d \n", program->statementsNum);
        return;
    }

    // Identifier �̸� ��
    const char* tests[] = {
        "x",
        "y",
        "foobar",
    };
    int len = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < len; i++) {
        Statement* stmt = program->statements[i];
        testLetStatement(stmt, tests[i]);
    }

    for (int i = 0; i < len; i++) {
        LetStatement* stmt = (LetStatement*)program->statements[i];

        free(stmt->token->literal);
        free(stmt->token);
        free(stmt->name);

        free(stmt);
    }

    free(program->statements);
    free(program);

    free(l->input);
    free(l);

    for (int i = 0; i < p->errorsNum; i++)
        free(p->errors[i]);
    free(p->errors);
    free(p);
}

int testLetStatement(Statement* s, const char* name) {
    if (s == NULL) {
        printf("Statement pointer is NULL\n");
        return 0;
    }


    if (strcmp(s->node.TokenLiteral(s), "let") != 0) {
        printf("s->node.TokenLiteral() not 'let'. got = %s\n", s->node.TokenLiteral(s));
        return 0;
    }

    
    // s�� LetStatement�� ����ȯ �����ϴٸ�
    LetStatement* letStmt = (LetStatement*)s;

    // Name �� ��
    if (strcmp(letStmt->name->value, name) != 0) {
        printf("letStmt->Name->value not '%s'. got = %s\n", name, letStmt->name->value);
        return 0;
    }

    // TokenLiteral() ����ؼ� ��
    if (strcmp(letStmt->name->node.TokenLiteral(letStmt->name), name) != 0) {
        printf("letStmt->Name->token.literal not '%s'. got = %s\n", name, letStmt->name->node.TokenLiteral(letStmt->name));
        return 0;
    }

    printf("\n--- LetStatement Details ---\n");
    printf("letStmt->Name->value: %s\n", letStmt->name->value);
    printf("letStmt->Name->token.literal: %s\n", letStmt->name->node.TokenLiteral(letStmt->name));
    printf("Name Token Literal: %s\n", letStmt->token->type);

    // Expression ��� (�ʿ�� ����)
    if (letStmt->value != NULL) {
        printf("Expression exists.\n");
        // Expression�� ���� ���� ���� ��� ����
    }
    else {
        printf("Expression is NULL.\n");
    }
    printf("----------------------------\n");

    return 1;
}


void TestReturnStatement() {
    const char* input = "return 5;"
        "return 10;"
        "return 993322;";

    Lexer* l = NewLexer(input);
    Parser* p = NewParser(l);

    Program* program = ParseProgram(p);
    checkParserErrors(p);

    int len = program->statementsNum;
    if (len != 3) {
        printf("program.Statements does not contain 3 statements. got = %d\n", len);
    }


    for (int i = 0; i < len; i++) {
        ReturnStatement* returnStmt = program->statements[i];

        if (strcmp(returnStmt->node.TokenLiteral(returnStmt), "return") != 0) {
            printf("returnStmt.TokenLiteral not \'return\', got %s\n", returnStmt->node.TokenLiteral(returnStmt));
        }
    }
}