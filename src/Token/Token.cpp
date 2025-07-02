#include "Token.h"
#include "TokenType.h"
#include <string>
#include <any>

Token::Token(TokenType type, string lexeme, std::any literal, int line):
    type(type), lexeme(lexeme), literal(literal), line(line) {}

std::string Token::toString(){
    // if(literal.type() == type(double)) std::to_string(literal)
    return type + " " + lexeme + " " + std::to_string(literal);
}

