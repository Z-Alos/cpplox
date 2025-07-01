#ifndef LOX_H
#define LOX_H

#include <string>

class Lox{
public:
    static bool hadError;

    static void runPrompt();

    static void runFile(const std::string& path);

private:
    static void run(std::string source);

    static void error(int line, std::string message); 

static void report(int line, std::string where, std::string message); 
};

#endif
