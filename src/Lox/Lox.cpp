#include "Lox.h"
// #include "Scanner/Scanner.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

void Lox::runPrompt(){
    while(true){
        string line;
        cout << "> ";

        if(!getline(cin, line)) break;
        Lox::run(line);
        hadError=false;
    }
}

void Lox::runFile(string& path){
    std::ifstream file(path);

    if(!file.is_open()){
        cerr << "Could not open file: " << path << endl;
        exit(74); // custom exit error code (file read failure)
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // read entire file into buffer
    Lox::run(buffer.str());

    if(hadError) exit(65);
}

void Lox::run(string source){
    Scanner scanner(source);

    std::vector<Token> tokens = scanner.scanTokens();

    for(const Token& token: tokens){
        cout << token << endl;
    }
}

void Lox::error(int line, string message) {
    report(line, "", message);
}

void Lox::report(int line, string where, string message) {
    cout << "[line " << line << "] Error" + where + ": " + message;
    hadError = true;
}

