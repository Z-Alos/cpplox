#ifndef SCANNER_H
#define SCANNER_H

#include "../Token/TokenType.h"
#include "../Token/Token.h"
#include <vector>
#include <string>
#include <any>

class Scanner {
private:
    int start = 0;
    int current = 0;
    int line = 1;
    std::string source;
    std::vector<Token> tokens;

public:
    Scanner(std::string source);

    std::vector<Token> scanTokens();

private:
    void scanToken();
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
    bool isDigit(char c);
    void identifier();
    void number();
    void String();
    bool match(char expected);
    char peek();
    char peekNext();
    char advance();
    bool isAtEnd();
    void addToken(TokenType type);
    void addToken(TokenType type, std::any literal);
};

#endif

