#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "TokenType.hpp"
#include <iostream>
using std::string;

class Token {
private:
    TokenType type;
    string lexeme;
    string literal;
    int line;

    Token(TokenType type, string lexeme, string literal, int line){
        this->type=type;
        this->lexeme=lexeme;
        this->literal=literal;
        this->line=line;
    }

public:
    string toString(){
        return type + " " + lexeme + " " + literal;
    }
};

#endif
