#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

class Lox{
public:
    static bool hadError=false;

    static void runPrompt(){
        while(true){
            string line;
            cout << "> ";

            if(!getline(cin, line)) break;
            run(line);
            hadError=false;
        }
    }

    static void runFile(string& path){
        std::ifstream file(path);

        if(!file.is_open()){
            cerr << "Could not open file: " << path << endl;
            exit(74); // custom exit error code (file read failure)
            std::stringstream buffer;
            buffer << file.rdbuf(); // read entire file into buffer
            run(buffer.str());

            if(hadError) return 65;
        }
    }

private:
    static void run(string source){
        Scanner scanner = new Scanner(source);
        vector<Token> tokens = scanner.scanTokens();

        for(const Token& token: tokens){
            cout << token << endl;
        }
    }
    static void error(int line, string message) {
        report(line, "", message);
    }

static void report(int line, string where, string message) {
        cout << "[line " << line << "] Error" + where + ": " + message;
        hadError = true;
    }
};

class Scanner{
public:

};

int main(int argc, char* argv[]){
    cout << "Hello, World!" << endl;

    if (argc > 2) {
        cout << "Usage: cpplox [script]";
        return 64; // exit with error
    } else if (argc == 2) { // runFile if path exist
        Lox::runFile(argv[1]);
    } else {
        Lox::runPrompt(); // run CLI input
    }

    return 0;
}


