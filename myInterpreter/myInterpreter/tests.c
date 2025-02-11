#include "tests.h"
#include"token.h"
#include "lexer.h"
#include "parser.h"
#include"ast.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


void lexer_test() {
	const char* input = "let five = 5; "
		"let ten = 10; "
		"let add = fn(x, y) { x + y; }; "
		"let result = add(five, ten);"
		"!-/*5;"
		"5 < 10 > 5;"
		"if (5 < 10) {"
		"	return true;"
		"}else{"
		"return false;"
		"}"
		"10 == 10;"
		"10 != 9;";


	Token tests[] = {
	{LET_TOKEN, "let"},
	{IDENT_TOKEN, "five"},
	{ASSIGN_TOKEN, "="},
	{INT, "5"},
	{SEMICOLON_TOKEN, ";"},
	{LET_TOKEN, "let"},
	{IDENT_TOKEN, "ten"},
	{ASSIGN_TOKEN, "="},
	{INT, "10"},
	{SEMICOLON_TOKEN, ";"},
	{LET_TOKEN, "let"},
	{IDENT_TOKEN, "add"},
	{ASSIGN_TOKEN, "="},
	{FUNCTION_TOKEN, "fn"},
	{LPAREN_TOKEN, "("},
	{IDENT_TOKEN, "x"},
	{COMMA_TOKEN, ","},
	{IDENT_TOKEN, "y"},
	{RPAREN_TOKEN, ")"},
	{LBRACE_TOKEN, "{"},
	{IDENT_TOKEN, "x"},
	{PLUS_TOKEN, "+"},
	{IDENT_TOKEN, "y"},
	{SEMICOLON_TOKEN, ";"},
	{RBRACE_TOKEN, "}"},
	{SEMICOLON_TOKEN, ";"},
	{LET_TOKEN, "let"},
	{IDENT_TOKEN, "result"},
	{ASSIGN_TOKEN, "="},
	{IDENT_TOKEN, "add"},
	{LPAREN_TOKEN, "("},
	{IDENT_TOKEN, "five"},
	{COMMA_TOKEN, ","},
	{IDENT_TOKEN, "ten"},
	{RPAREN_TOKEN, ")"},
	{SEMICOLON_TOKEN, ";"},
	{BANG_TOKEN, "!"},
	{MINUS_TOKEN, "-"},
	{SLASH_TOKEN, "/"},
	{ASTERISK_TOKEN, "*"},
	{INT, "5"},
	{SEMICOLON_TOKEN, ";"},
	{INT, "5"},
	{LT_TOKEN, "<"},
	{INT, "10"},
	{GT_TOKEN, ">"},
	{INT, "5"},
	{SEMICOLON_TOKEN, ";"},
	{IF_TOKEN, "if"},
	{LPAREN_TOKEN, "("},
	{INT, "5"},
	{LT_TOKEN, "<"},
	{INT, "10"},
	{RPAREN_TOKEN, ")"},
	{LBRACE_TOKEN, "{"},
	{RETURN_TOKEN, "return"},
	{TRUE_TOKEN, "true"},
	{SEMICOLON_TOKEN, ";"},
	{RBRACE_TOKEN, "}"},
	{ELSE_TOKEN, "else"},
	{LBRACE_TOKEN, "{"},
	{RETURN_TOKEN, "return"},
	{FALSE_TOKEN, "false"},
	{SEMICOLON_TOKEN, ";"},
	{RBRACE_TOKEN, "}"},
	{INT, "10"},
	{EQ_TOKEN, "=="},
	{INT, "10"},
	{SEMICOLON_TOKEN, ";"},
	{INT, "10"},
	{NOT_EQ_TOKEN, "!="},
	{INT, "9"},
	{SEMICOLON_TOKEN, ";"},
	{EOF_TOKEN, ""}
	};


	Lexer* lexer = NewLexer(input);
	//렉서를 만든후 분휴 시작

	int len = sizeof(tests) / sizeof(Token);

	for (int i = 0; i < len; i++) {
		Token* tok = NextToken(lexer);

		if (tok->type != tests[i].type) {
			printf("tests[%d] - tokentype wrong. expected = %s, got = %s\n", i, tests[i].type, tok->type);
		}

		if (strcmp(tok->literal, tests[i].literal) != 0) {
			printf("tests[%d] - literal wrong. expected = %s, got = %s\n", i, tests[i].literal, tok->literal);
		}

		printf("tests[%d]'s type = %s, literal = %s\n", i, tests[i].type, tok->literal);
		//free(tok->literal);
		free(tok);
	}

	free(lexer->input);
	free(lexer);
	//l은 input을 렉서해서 받아옴
	//받아온다면 tests랑 비교하기
}


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
    Parser* p = NewParser(l); // 렉서를 가지고 파서 만듬

    Program* program = ParseProgram(p); // 파싱된 결과를 프로그램 AST로 만듬
    checkParserErrors(p);
    if (program == NULL) {
        printf("ParseProgram() returned NULL!\n");
        return;
    }

    if (program->statementsNum != 3) {
        printf("Statements do not contain 3 statements. got = %d \n", program->statementsNum);
        return;
    }

    // Identifier 이름 비교
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

    freeProgram(program);
    freeParser(p);
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

    
    // s가 LetStatement로 형변환 가능하다면
    LetStatement* letStmt = (LetStatement*)s;

    // Name 값 비교
    if (strcmp(letStmt->name->value, name) != 0) {
        printf("letStmt->Name->value not '%s'. got = %s\n", name, letStmt->name->value);
        return 0;
    }

    // TokenLiteral() 사용해서 비교
    if (strcmp(letStmt->name->node.TokenLiteral(letStmt->name), name) != 0) {
        printf("letStmt->Name->token.literal not '%s'. got = %s\n", name, letStmt->name->node.TokenLiteral(letStmt->name));
        return 0;
    }

    printf("\n--- LetStatement Details ---\n");
    printf("letStmt->Name->value: %s\n", letStmt->name->value);
    printf("letStmt->Name->token.literal: %s\n", letStmt->name->node.TokenLiteral(letStmt->name));
    printf("Name Token Literal: %s\n", letStmt->token->type);

    // Expression 출력 (필요시 구현)
    if (letStmt->value != NULL) {
        printf("Expression exists.\n");
        // Expression에 대한 세부 정보 출력 가능
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

        if (strcmp(returnStmt->statement.node.TokenLiteral(returnStmt), "return") != 0) {
            printf("returnStmt.TokenLiteral not \'return\', got %s\n", returnStmt->statement.node.TokenLiteral(returnStmt));
        }
    }

    freeProgram(program);
    freeParser(p);
}

void TestString()
{
    Program* program = newProgram();

    // LetStatement 생성
    LetStatement* letStmt = newLetStatement();
    letStmt->token = (Token*)malloc(sizeof(Token));
    letStmt->token->type = LET_TOKEN;  // "LET" 토큰 사용
    letStmt->token->literal = _strdup("let");

    // Identifier 생성 및 설정
    Identifier* identifier1 = newIdentifier();
    identifier1->token = (Token*)malloc(sizeof(Token));
    identifier1->token->type = IDENT_TOKEN;   // "IDENT" 토큰
    identifier1->token->literal = _strdup("myVar");
    identifier1->value = _strdup("myVar");     // Identifier 값 저장

    // LetStatement에 Identifier 연결
    letStmt->name = identifier1;

    ExpressionStatement* es = newExpressionStatement();
    es->token = (Token*)malloc(sizeof(Token));
    es->token->type = IDENT_TOKEN;   // "IDENT" 토큰
    es->token->literal = _strdup("anotherVar");


    letStmt->value = es;
    // Program에 LetStatement 추가
    program->statementsNum = 1;
    program->statements = (Statement**)malloc(sizeof(Statement*));
    program->statements[0] = (Statement*)letStmt;

    // 출력 확인
    printf("%s\n", printProgram(program));

    // 메모리 해제
    freeProgram(program);


}
