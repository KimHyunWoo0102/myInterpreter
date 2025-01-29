#include "lexer.h"
#include "token.h"
#include "ast.h"
#include "parser.h"

// lexer.c 관련 메모리 해제 함수 정의
void freeLexer(Lexer* lexer) {
    if (!lexer) return;
    free(lexer->input);
    free(lexer);
}

// token.c 관련 메모리 해제 함수 정의
void freeToken(Token* token) {
    if (!token) return;
    free(token->literal);
    free(token);
}

// ast.c 관련 메모리 해제 함수 정의
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
    // 여기에 추가적인 메모리 해제 로직을 추가할 수 있습니다.
    free(stmt);
}

// parser.c 관련 메모리 해제 함수 정의
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
