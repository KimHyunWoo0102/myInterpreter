#include "repl.h"
#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void start(FILE*in,FILE*out)
{
	char line[MAX_LIEN_LENGTH];

	while (true) {
		fprintf(out, PROMPT);

		if (fgets(line, MAX_LIEN_LENGTH, in) == NULL) {
			break; //EOF 또는 오류
		}

		//개행문자 제거
		size_t len = strlen(line);
		if (len > 0 && line[len - 1] == '\n') {
			line[len - 1] = '\0';
		}

		Lexer* lexer = NewLexer(line);

		while (true) {
			Token *tok = NextToken(lexer);

			if (strcmp(tok->type, EOF_TOKEN) == 0) {
				break;
			}
			fprintf(out, "{Type:%s, Literal:%s}\n", tok->type, tok->literal);
		}

		free(lexer);
	}
}
