#include "TokenType.hpp"
#include <vector>
#include <string>

class Scanner{
private:
    int start=0, current=0, line=1;
    std::string source;
    List<Token> tokens = std::vector;

    Scanner(std::string source): source(source){
    }

    List<Token> scanTokens(){
        while(!isAtEnd()){
            start=current;
            scanToken();

            tokens.push_back(
            return tokens;
        }
    }

    void scanToken(){
        char c = advance();

        switch (c) {
            case '(': addToken(LEFT_PAREN); break;
            case ')': addToken(RIGHT_PAREN); break;
            case '{': addToken(LEFT_BRACE); break;
            case '}': addToken(RIGHT_BRACE); break;
            case ',': addToken(COMMA); break;
            case '.': addToken(DOT); break;
            case '-': addToken(MINUS); break;
            case '+': addToken(PLUS); break;
            case ';': addToken(SEMICOLON); break;
            case '*': addToken(STAR); break;
        }

    }

    char advance(){
        current++;
        return source[current-1];
    }



    bool isAtEnd(){
        return current>=source.size();
    }

};

