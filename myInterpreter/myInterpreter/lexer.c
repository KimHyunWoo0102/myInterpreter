#include "lexer.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

Lexer* New(char* input)
{
    //��ǲ ������ ���Ӱ� Lexer ����ü ���� input �����صδ� �Լ�
    Lexer* l = (Lexer*)malloc(sizeof(Lexer));

    l->input = _strdup(input);

    if (!l->input) {
        fprintf(stderr, "Memory allocation failed for input string\n");
        free(l);
        exit(EXIT_FAILURE);
    }//��ǲ�� ������ �����޽��� ������ ����

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
        tok = newToken(ASSIGN_TOKEN, lch);
        break;
    case ';':
        tok = newToken(SEMICOLON_TOKEN, lch);
        break;
    case '(':
        tok = newToken(LPAREN_TOKEN, lch);
        break;
    case ')':
        tok = newToken(RPAREN_TOKEN, lch);
        break;
    case ',':
        tok = newToken(COMMA_TOKEN, lch);
        break;
    case '+':
        tok = newToken(PLUS_TOKEN, lch);
        break;
    case '{':
        tok = newToken(LBRACE_TOKEN, lch);
        break;
    case '}':
        tok = newToken(RBRACE_TOKEN, lch);
        break;
    case 0:
        tok = (Token*)malloc(sizeof(Token));

        if (tok == NULL) {
            printf("Memory allocation failed for tok.\n");
            exit(1); // ���α׷� ����
        }

        tok->type = EOF_TOKEN;
        tok->literal = _strdup("");
        break;
    }

    readChar(lexer);

    return tok;
}


Token*newToken(TokenType token, char* input)
{
    Token* newToken = (Token*)malloc(sizeof(Token));
    char* str = (char*)malloc(2);
    str[0] = input;  // �Է¹��� char�� ù ��° ��ġ�� ����
    str[1] = '\0';   // ���ڿ� ���� ���� �߰�

    //��ū ������ input �޾Ƽ� ���ͷ� ó�����Ŀ� ��ū ��ü �����ֱ�
    //newToken->literal = _strdup(TokenTypeNames[token]);
    //�׳� ������ ��� �����ͷ� ����Ű�⸸ �Ұǵ� �̷��� �ص� �ɵ�...?
    newToken->type = token;
    newToken->literal = _strdup(str);
    return newToken;
}
