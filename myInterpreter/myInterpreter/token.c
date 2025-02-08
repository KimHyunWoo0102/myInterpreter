#include "token.h"
#include<stdio.h>
#include<stdlib.h>

void freeToken(Token* token)
{
	if (token->literal != NULL)
		free(token->literal);

	free(token);
}
