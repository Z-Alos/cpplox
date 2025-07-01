#include "TokenType.hpp"
#include "Token.hpp"
#include <vector>
#include <string>

class Scanner{
private:
    int start=0, current=0, line=1;
    std::string source;
    std::vector<Token> tokens;

    Scanner(std::string source): source(source){
    }

    std::vector<Token> scanTokens(){
        while(!isAtEnd()){
            start=current;
            scanToken();

        }

        tokens.push_back(new Token(EOF, "", "", line));
        return tokens;
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

            default: Lox.error(line, "Unexpected character"); break;
        }

    }

    void String(){
        while(peek() != '"' && !isAtEnd()){
            if(peek() == '\n') line++;
            advance();
        }

        if(isAtEnd()){
            Lox.error(line, "Unterminated string.");
            return;
        }

        return;
    }

    bool match(char expected){
        if(isAtEnd()) return false;
        if(source[current] != expected) return false;

        current++;
        return true;
    }

    char peek(){
        return isAtEnd() ? '\0' : source[current];
    }

    char advance(){
        current++;
        return source[current-1];
    }

    bool isAtEnd(){
        return current>=source.size();
    }

    void addToken(TokenType type){
        addToken(type, "");
    }

    void addToken(TokenType type, string literal){
        string text=source.substr(start, current); 
        tokens.push_back(new Token(type, text, literal, line));
    }

};

