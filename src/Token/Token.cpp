#include "Token.h"
#include "TokenType.h"
#include <string>
#include <any>

TokenType type;
std::string lexeme;
std::any literal;
int line;

std::string Token::toString(){
    return type + " " + lexeme + " " + literal;
}

