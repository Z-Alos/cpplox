#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"
#include <string>
#include <any>

using std::string;

class Token {
public:
    TokenType type;
    string lexeme;
    std::any literal;
    int line;

    Token(TokenType type, string lexeme, std::any literal, int line);

public:
    string toString();
};

#endif
