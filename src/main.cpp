#include "Lox/Lox.h"
#include <iostream>

int main(int argc, char* argv[]){
    std::cout << "Hello, World!" << std::endl;

    if (argc > 2) {

        std::cout << "Usage: cpplox [script]";
        return 64; // exit with error
                   //
    } else if (argc == 2) { // runFile if path exist
                            //
        Lox::runFile(argv[1]);

    } else {

        Lox::runPrompt(); // run CLI input

    }

    return 0;
}


