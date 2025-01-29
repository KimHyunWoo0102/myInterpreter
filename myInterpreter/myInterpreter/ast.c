#include "ast.h"
#include<string.h>


const char* letTokenLiteral(void* self) {
    LetStatement* ls = (LetStatement*)self; // self를 LetStatement로 변환
    return ls->token->literal;  // LetStatement에 대한 TokenLiteral 반환
}

const char* identifierTokenLiteral(void* self) {
    Identifier* id = (Identifier*)self; // self를 Identifier로 변환
    return id->token->literal;  // Identifier에 대한 TokenLiteral 반환
}

// Program 메서드 구현 (프로그램에서 첫 번째 Statement의 TokenLiteral 호출)
const char* programTokenLiteral(Program* p) {
    if (p->statementsNum > 0) {
        return p->statements[0]->node.TokenLiteral(p->statements[0]);
    }
    return "";
}

// LetStatement 및 Identifier 객체 생성 함수
LetStatement* newLetStatement() {
    LetStatement* ls = (LetStatement*)malloc(sizeof(LetStatement));
    // LetStatement의 TokenLiteral 함수 포인터를 설정
    ls->node.TokenLiteral = letTokenLiteral;

    return ls;
}

Identifier* newIdentifier() {
    Identifier* id = (Identifier*)malloc(sizeof(Identifier));
   
    id->TokenLiteral = identifierTokenLiteral;
    return id;
}



