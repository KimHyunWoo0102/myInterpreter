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

char peekChar(Lexer* l)
{
    if (l->readPosition >= strlen(l->input)) {
        return 0;//������ �Ѿ�� 0 ����
    }
    else {
        return l->input[l->readPosition];
    }
}

char* readNumber(Lexer* lexer)
{
    int position = lexer->position;

    while (isDigit(lexer->ch)) {
        readChar(lexer);
    }
    const int len = lexer->position - position;
    char* str = (char*)malloc(len + 1);

    if (str == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    strncpy_s(str, len + 1, lexer->input + position, len);

    return str;
}

Token* NextToken(Lexer* lexer)
{
    Token *tok=NULL;

    skipWhitespace(lexer);

    char lch = lexer->ch;

    switch (lch)
    {
    case '=':
        if (peekChar(lexer) == '=') {
            readChar(lexer);
            tok = (Token*)malloc(sizeof(Token));

            tok->type = EQ_TOKEN;
            tok->literal = "==";
        }else tok = newToken(ASSIGN_TOKEN, lch);
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
    case '-':
        tok = newToken(MINUS_TOKEN, lch);
        break;
    case '!':
        if (peekChar(lexer) == '=') {
            readChar(lexer);
            tok = (Token*)malloc(sizeof(Token));

            tok->type = NOT_EQ_TOKEN;
            tok->literal = "!=";
        }
        else tok = newToken(BANG_TOKEN, lch);
        break;
    case '*':
        tok = newToken(ASTERISK_TOKEN, lch);
        break;
    case '/':
        tok = newToken(SLASH_TOKEN, lch);
        break;
    case '<':
        tok = newToken(LT_TOKEN, lch);
        break;
    case '>':
        tok = newToken(GT_TOKEN, lch);
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

    default:
        if (isLetter(lch)) {
            tok = (Token*)malloc(sizeof(Token));

            if (tok == NULL) {
                printf("Memory allocation failed for tok.\n");
                exit(1); // ���α׷� ����
            }

            tok->literal = _strdup(readIdentifier(lexer));
            tok->type = LookupIdent(tok->literal);
            return tok;
        }
        else if (isDigit(lch)) {
            tok = (Token*)malloc(sizeof(Token));

            if (tok == NULL) {
                printf("Memory allocation failed for tok.\n");
                exit(1); // ���α׷� ����
            }

            tok->type = INT;
            tok->literal = readNumber(lexer);

            return tok;
        }
        else {
            tok = newToken(ILLEGAL_TOKEN, lch);
        }
    }

    readChar(lexer);

    return tok;
}


Token*newToken(TokenType token, char input)
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

void skipWhitespace(Lexer* l)
{
    while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r')
        readChar(l);
}

bool isLetter(char ch)
{
    return 'a'<=ch&&ch<='z'||'A'<=ch&&ch<='Z'||ch=='_';
}

bool isDigit(char ch)
{
    return '0'<=ch&&ch<='9';
}

char* readIdentifier(Lexer* l)
{
    int position = l->position;
    while (isLetter(l->ch)) {
        readChar(l);
    }

    const int len = l->position - position;
    char* str = (char*)malloc(len + 1);

    if (str == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    strncpy_s(str, len + 1, l->input + position, len);

    return str;
}

const char* LookupIdent(const char* ident) {
    if (strcmp(ident, "fn") == 0) {
        return FUNCTION_TOKEN;
    }
    if (strcmp(ident, "let") == 0) {
        return LET_TOKEN;
    }
    if (strcmp(ident, "true") == 0) {
        return TRUE_TOKEN;
    }
    if (strcmp(ident, "false") == 0) {
        return FALSE_TOKEN;
    }
    if (strcmp(ident, "if") == 0) {
        return IF_TOKEN;
    }
    if (strcmp(ident, "else") == 0) {
        return ELSE_TOKEN;
    }
    if (strcmp(ident, "return") == 0) {
        return RETURN_TOKEN;
    }

    return IDENT_TOKEN;  // ��Ī�Ǵ� Ű���尡 ������ IDENT ��ȯ
}
