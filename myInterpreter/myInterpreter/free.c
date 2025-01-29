#include "lexer.h"
#include "token.h"
#include "ast.h"
#include "parser.h"

// lexer.c ���� �޸� ���� �Լ� ����
void freeLexer(Lexer* lexer) {
    if (!lexer) return;
    free(lexer->input);
    free(lexer);
}

// token.c ���� �޸� ���� �Լ� ����
void freeToken(Token* token) {
    if (!token) return;
    free(token->literal);
    free(token);
}

// ast.c ���� �޸� ���� �Լ� ����
void freeProgram(Program* program) {
    if (!program) return;
    for (size_t i = 0; i < program->statementsNum; i++) {
        freeStatement(program->statements[i]);
    }
    free(program->statements);
    free(program);
}

void freeLetStatement(LetStatement* stmt) {
    if (!stmt) return;
    free(stmt->name->value);
    free(stmt->name);
    free(stmt);
}

void freeIdentifier(Identifier* id) {
    if (!id) return;
    free(id->value);
    free(id);
}

void freeStatement(Statement* stmt) {
    if (!stmt) return;
    // ���⿡ �߰����� �޸� ���� ������ �߰��� �� �ֽ��ϴ�.
    free(stmt);
}

// parser.c ���� �޸� ���� �Լ� ����
void freeParser(Parser* parser) {
    if (!parser) return;
    freeErrors(parser);
    free(parser);
}

void freeErrors(Parser* parser) {
    if (parser->errors) {
        for (int i = 0; i < parser->errorCount; i++) {
            free(parser->errors[i]);
        }
        free(parser->errors);
        parser->errors = NULL;
        parser->errorCount = 0;
    }
}
