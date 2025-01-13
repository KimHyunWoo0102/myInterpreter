#include<stdio.h>
#include "token.h"
#include "lexer.h"
#include<string.h>

int main() {
	const char* input = "=+(){},;";
	
	Token tests[] = {
		{ASSIGN_TOKEN,"="},
		{PLUS_TOKEN,"+"},
		{LPAREN_TOKEN,"("},
		{RPAREN_TOKEN,")"},
		{LBRACE_TOKEN,"{"},
		{RBRACE_TOKEN,"}"},
		{COMMA_TOKEN,","},
		{SEMICOLON_TOKEN,";"},
		{EOF_TOKEN,""}
	};

	Lexer* lexer = New(input);
	
	int len = sizeof(tests) / sizeof(Token);
	for (int i = 0; i < len; i++) {
		Token* tok = NextToken(lexer);

		if (tok->type != tests[i].type) {
			printf("tests[%d] - tokentype wrong. expected = %d, got = %d\n", i, tests[i].type, tok->type);
		}

		if (strcmp(tok->literal, tests[i].literal) != 0) {
			printf("tests[%d] - literal wrong. expected = %s, got = %s\n", i, tests[i].literal, tok->literal);
		}

		free(tok->literal);
		free(tok);
	}

	free(lexer->input);
	free(lexer);
	//l은 input을 렉서해서 받아옴
	//받아온다면 tests랑 비교하기
}
