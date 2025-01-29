#include "parser_test.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void parser_test()
{
    const char* input =
        "let x = 5;"
        "let y = 10;"
        "let foobar = 838383;";

    Lexer* l = NewLexer(input);
    Parser* p = NewParser(l); // ������ ������ �ļ� ����

    Program* program = ParseProgram(p); // �Ľ̵� ����� ���α׷� AST�� ����

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
    if (strcmp(letStmt->name->TokenLiteral(letStmt->name), name) != 0) {
        printf("letStmt->Name->token.literal not '%s'. got = %s\n", name, letStmt->name->TokenLiteral(letStmt->name));
        return 0;
    }

    printf("\n--- LetStatement Details ---\n");
    printf("letStmt->Name->value: %s\n", letStmt->name->value);
    printf("letStmt->Name->token.literal: %s\n", letStmt->name->TokenLiteral(letStmt->name));
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
