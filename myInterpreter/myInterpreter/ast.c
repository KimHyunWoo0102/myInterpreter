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
const char* returnTokenLiteral(void* self)
{
    ReturnStatement* rs = (ReturnStatement*)self;
    return rs->token->literal;
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
    ls->node.statementType = LET;
    return ls;
}

Identifier* newIdentifier() {
    Identifier* id = (Identifier*)malloc(sizeof(Identifier));
   
    id->node.TokenLiteral = identifierTokenLiteral;
    id->node.statementType = IDENTIFIER;
    return id;
}

ReturnStatement* newReturnStatement()
{
    ReturnStatement* rs = (ReturnStatement*)malloc(sizeof(ReturnStatement));
    rs->node.TokenLiteral = returnTokenLiteral;
    rs->node.statementType = RETURN;
    return rs;
}


