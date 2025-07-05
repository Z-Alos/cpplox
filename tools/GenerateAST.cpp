#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../utils/utils.h"

void defineType(std::ofstream& file, const std::string& baseName,
                const std::string& className, const std::string& fieldList) {
    file << "class " << className << " : public " << baseName << " {\n";
    file << "public:\n";

    // Constructor
    file << "    " << className << "(" << fieldList << ")";
    
    std::vector<std::string> fields = utils::split(fieldList, ',');
    if (!fields.empty()) {
        file << "\n        : ";
        for (size_t i = 0; i < fields.size(); ++i) {
            std::string field = utils::trim(fields[i]);
            std::string name = field.substr(field.find_last_of(' ') + 1);
            file << name << "(" << name << ")";
            if (i < fields.size() - 1) file << ", ";
        }
    }

    file << " {}\n\n";

    // Fields
    for (std::string& field : fields) {
        field = utils::trim(field);
        std::string type = field.substr(0, field.find_last_of(' '));
        std::string name = field.substr(field.find_last_of(' ') + 1);
        file << "    " << type << " " << name << ";\n";
    }

    file << "};\n\n";
}

void defineAst(const std::string& outputDir, const std::string& baseName,
               const std::vector<std::string>& types) {
    std::string path = outputDir + "/" + baseName + ".h";
    std::ofstream file(path);

    file << "#pragma once\n\n";
    file << "#include \"../src/Token/Token.h\";\n\n";
    file << "using Object = std::variant<std::monostate, double, std::string, bool>;\n\n";
    file << "// find and replace operator with operator_";
    file << "class " << baseName << " {\n";
    file << "public:\n";
    file << "    virtual ~" << baseName << "() = default;\n";
    file << "};\n\n";

    for (const std::string& type : types) {
        std::vector<std::string> parts = utils::split(type, ':');
        std::string className = utils::trim(parts[0]);
        std::string fields = utils::trim(parts[1]);

        defineType(file, baseName, className, fields);
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: generate_ast <output directory>\n";
        return 64;
    }

    std::string outputDir = argv[1];
    std::vector<std::string> types = {
        "Binary : Expr* left, Token operator, Expr* right",
        "Grouping : Expr* expression",
        "Literal : Object value",
        "Unary : Token operator, Expr* right"
    };

    defineAst(outputDir, "Expr", types);
    return 0;
}

