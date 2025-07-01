#include "Scanner.h"
#include "../Lox/Lox.h"
#include "../Token/TokenType.h"
#include "../Token/Token.h"
#include <vector>
#include <string>
#include <any>

std::vector<Token> Scanner::scanTokens(){
    while(!isAtEnd()){
        start=current;
        scanToken();
    }

    tokens.push_back(Token token(EOF, "", "", line));
    return tokens;
}

void Scanner::scanToken(){
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

        case '!':
                  addToken(match('=') ? BANG_EQUAL : BANG);
                  break;
        case '=':
                  addToken(match('=') ? EQUAL_EQUAL : EQUAL);
                  break;
        case '<':
                  addToken(match('=') ? LESS_EQUAL : LESS);
                  break;
        case '>':
                  addToken(match('=') ? GREATER_EQUAL : GREATER);
                  break;
        case '/':
                  if(match('/')){ // check if double-slash: comment
                      while(peek() != '\n' && !isAtEnd()) advance();
                  }
                  else{ // divisor
                      addToken(SLASH);
                  }
                  break;

        case ' ':
        case '\r':
        case '\t':
                  // Ignore whitespace
                  break;
        case '\n':
                  line++;
                  break;

        default: 
                  if(isDigit(c)) number();
                  else Lox.error(line, "Unexpected character");
                  break;
    }

}

void Scanner::number(){
    while(isDigit(peek())) advance();

    // check for decimal
    if(peek() == '.' && isDigit(peekNext())){
        advance(); // consume .
        while(isDigit(peek())) advance();
    }

    addToken(NUMBER, std::stod(source.substr(start, current-start-1)));
}

bool Scanner::isDigit(char c){
    return c >= '0' && c <= '9';
}

void Scanner::String(){
    while(peek() != '"' && !isAtEnd()){
        if(peek() == '\n') line++;
        advance();
    }

    if(isAtEnd()){
        Lox.error(line, "Unterminated string.");
        return;
    }

    advance();

    std::string value = source.substr(start+1, current-start-1);
    addToken(STRING, value);

    return;
}

bool Scanner::match(char expected){
    if(isAtEnd()) return false;
    if(source[current] != expected) return false;

    current++;
    return true;
}

char Scanner::peek(){
    return isAtEnd() ? '\0' : source[current];
}

char Scanner::peekNext(){
    if(current+1 >= source.size()) return '\0';
    return source[current+1];
}

char Scanner::advance(){
    current++;
    return source[current-1];
}

bool Scanner::isAtEnd(){
    return current>=source.size();
}

void Scanner::addToken(TokenType type){
    addToken(type, "");
}

void Scanner::addToken(TokenType type, std::any literal){
    string text=source.substr(start, current); 
    tokens.push_back(new Token(type, text, literal, line));
}

