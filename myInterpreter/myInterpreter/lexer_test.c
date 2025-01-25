#include<stdio.h>
#include "token.h"
#include "lexer.h"
#include<string.h>

int main() {
	const char* input = "let five = 5; "
		"let ten = 10; "
		"let add = fn(x, y) { x + y; }; "
		"let result = add(five, ten);";

	
	Token tests[] = {
		{LET_TOKEN,"let"},
		{IDENT_TOKEN,"five"},
		{ASSIGN_TOKEN,"="},
		{INT,"5"},
		{SEMICOLON_TOKEN,";"},
		{LET_TOKEN,"let"},
		{IDENT_TOKEN,"ten"},
		{ASSIGN_TOKEN,"="},
		{INT,"10"},
		{SEMICOLON_TOKEN,";"},
		{LET_TOKEN,"let"},
		{IDENT_TOKEN,"add"},
		{ASSIGN_TOKEN,"="},
		{FUNCTION_TOKEN,"fn"},
		{LPAREN_TOKEN,"("},
		{IDENT_TOKEN,"x"},
		{COMMA_TOKEN,","},
		{IDENT_TOKEN,"y"},
		{RPAREN_TOKEN,")"},
		{LBRACE_TOKEN,"{"},
		{IDENT_TOKEN,"x"},
		{PLUS_TOKEN,"+"},
		{IDENT_TOKEN,"y"},
		{SEMICOLON_TOKEN,";"},
		{RBRACE_TOKEN,"}"},
		{SEMICOLON_TOKEN,";"},
		{LET_TOKEN,"let"},
		{IDENT_TOKEN,"result"},
		{ASSIGN_TOKEN,"="},
		{IDENT_TOKEN,"add"},
		{LPAREN_TOKEN,"("},
		{IDENT_TOKEN,"five"},
		{COMMA_TOKEN,","},
		{IDENT_TOKEN,"ten"},
		{RPAREN_TOKEN,")"},
		{SEMICOLON_TOKEN,";"},
		{EOF_TOKEN,""},
	};//테스트케이스 생성

	Lexer* lexer = New(input);
	//렉서를 만든후 분휴 시작

	int len = sizeof(tests) / sizeof(Token);
	
	for (int i = 0; i < len; i++) {
		Token* tok = NextToken(lexer);

		if (tok->type != tests[i].type) {
			printf("tests[%d] - tokentype wrong. expected = %s, got = %s\n", i,tests[i].type, tok->type);
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
