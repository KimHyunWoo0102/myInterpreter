#include "lexer.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

Lexer* New(char* input)
{
    Lexer* l = (Lexer*)malloc(sizeof(Lexer));

    l->input = _strdup(input);
    if (!l->input) {
        fprintf(stderr, "Memory allocation failed for input string\n");
        free(l);
        exit(EXIT_FAILURE);
    }

    l->ch = 0;
    l->position = 0;
    l->readPosition = 0;
    readChar(l);

    return l;
}

void readChar(Lexer* lexer)
{
    if (lexer->readPosition > strlen(lexer->input)){
        lexer->ch = 0;//������ �Ѿ�� ch�� 0�ֱ�
    }
    else {
        lexer->ch = lexer->input[lexer->readPosition];
    }

    lexer->position = lexer->readPosition;
    (lexer->readPosition)++;
    //�̸� ���캸�� �ص� �ǳ� �˻�
    //���� ���� ���ڸ� �ϴ� ������ �ؾ��ϴ�
}

Token* NextToken(Lexer* lexer)
{
    Token *tok=NULL;
    char lch = lexer->ch;

    switch (lch)
    {
    case '=':
        tok = newToken(ASSIGN_TOKEN);
        break;
    case ';':
        tok = newToken(SEMICOLON_TOKEN);
        break;
    case '(':
        tok = newToken(LPAREN_TOKEN);
        break;
    case ')':
        tok = newToken(RPAREN_TOKEN);
        break;
    case ',':
        tok = newToken(COMMA_TOKEN);
        break;
    case '+':
        tok = newToken(PLUS_TOKEN);
        break;
    case '{':
        tok = newToken(LBRACE_TOKEN);
        break;
    case '}':
        tok = newToken(RBRACE_TOKEN);
        break;
    case 0:
        tok = (Token*)malloc(sizeof(Token));
        tok->type = EOF_TOKEN;
        tok->literal = _strdup("");
        break;
    }

    readChar(lexer);

    return tok;
}


Token*newToken(TokenType token)
{
    Token* newToken = (Token*)malloc(sizeof(Token));
    newToken->literal = _strdup(TokenTypeNames[token]);
    newToken->type = token;
    return newToken;
}
