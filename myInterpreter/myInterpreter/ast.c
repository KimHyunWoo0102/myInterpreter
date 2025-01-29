#include "ast.h"
#include<string.h>


const char* letTokenLiteral(void* self) {
    LetStatement* ls = (LetStatement*)self; // self�� LetStatement�� ��ȯ
    return ls->token->literal;  // LetStatement�� ���� TokenLiteral ��ȯ
}

const char* identifierTokenLiteral(void* self) {
    Identifier* id = (Identifier*)self; // self�� Identifier�� ��ȯ
    return id->token->literal;  // Identifier�� ���� TokenLiteral ��ȯ
}

// Program �޼��� ���� (���α׷����� ù ��° Statement�� TokenLiteral ȣ��)
const char* programTokenLiteral(Program* p) {
    if (p->statementsNum > 0) {
        return p->statements[0]->node.TokenLiteral(p->statements[0]);
    }
    return "";
}

// LetStatement �� Identifier ��ü ���� �Լ�
LetStatement* newLetStatement() {
    LetStatement* ls = (LetStatement*)malloc(sizeof(LetStatement));
    // LetStatement�� TokenLiteral �Լ� �����͸� ����
    ls->node.TokenLiteral = letTokenLiteral;

    return ls;
}

Identifier* newIdentifier() {
    Identifier* id = (Identifier*)malloc(sizeof(Identifier));
   
    id->TokenLiteral = identifierTokenLiteral;
    return id;
}



