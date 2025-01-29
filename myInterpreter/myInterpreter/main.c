#include"repl.h"
#include <windows.h>
#include <lmcons.h>
#include <stdio.h>
#include "lexer_test.h"
#include"parser_test.h"

int main() {
  	parser_test();
	/*char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;

	GetUserName(username, &username_len);

	printf("Hello %s! This is the Monkey programming lauguage!\n", username);
	printf("Feel free to type in commands\n");
	start(stdin, stdout);*/
	return 0;
}