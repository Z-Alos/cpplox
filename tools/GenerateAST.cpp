#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../utils/utils.h"

void defineVisitor(std::ofstream& file, const std::string& baseName, const std::vector<std::string>& types) {
    for (const std::string& type : types) {
        std::vector<std::string> parts = utils::split(type, ':');
        std::string typeName = utils::trim(parts[0]);
        file << "class " << typeName << ";\n";
    }
    file << "\n";
    file << "template <typename R>\n";
    file << "struct Visitor {\n";
    for (const std::string& type : types) {
        std::vector<std::string> parts = utils::split(type, ':');
        std::string typeName = utils::trim(parts[0]);
        file << "    virtual R visit" << typeName << baseName << "(const " << typeName << "* " << utils::toLowerCase(baseName) << ") = 0;\n";
    }
    file << "};\n\n";
}

void defineType(std::ofstream& file, const std::string& baseName, const std::string& className, const std::string& fieldList) {
    file << "class " << className << " : public " << baseName << " {\n";
    file << "public:\n";
    std::vector<std::string> fields = utils::split(fieldList, ',');
    file << "    " << className << "(";
    for (size_t i = 0; i < fields.size(); ++i) {
        std::string field = utils::trim(fields[i]);
        std::string type = field.substr(0, field.find_last_of(' '));
        std::string name = field.substr(field.find_last_of(' ') + 1);
        std::string paramName = (name == "operator") ? "operator_" : name;
        file << type << " " << paramName;
        if (i < fields.size() - 1) file << ", ";
    }
    file << ")";
    if (!fields.empty()) {
        file << "\n        : ";
        for (size_t i = 0; i < fields.size(); ++i) {
            std::string field = utils::trim(fields[i]);
            std::string name = field.substr(field.find_last_of(' ') + 1);
            std::string paramName = (name == "operator") ? "operator_" : name;
            file << paramName << "(" << paramName << ")";
            if (i < fields.size() - 1) file << ", ";
        }
    }
    file << " {}\n\n";
    for (std::string& field : fields) {
        field = utils::trim(field);
        std::string type = field.substr(0, field.find_last_of(' '));
        std::string name = field.substr(field.find_last_of(' ') + 1);
        std::string paramName = (name == "operator") ? "operator_" : name;
        file << "    " << type << " " << paramName << ";\n";
    }
    file << "\n    template <typename R>\n";
    file << "    R accept(Visitor<R>* visitor) const override {\n";
    file << "        return visitor->visit" << className << baseName << "(this);\n";
    file << "    }\n";
    file << "};\n\n";
}

void defineAst(const std::string& outputDir, const std::string& baseName, const std::vector<std::string>& types) {
    std::string path = outputDir + "/" + baseName + ".h";
    std::ofstream file(path);
    file << "#pragma once\n\n";
    file << "#include \"../src/Token/Token.h\"\n";
    file << "#include <variant>\n";
    file << "#include <string>\n";
    file << "using Object = std::variant<std::monostate, double, std::string, bool>;\n\n";
    defineVisitor(file, baseName, types);
    file << "class " << baseName << " {\n";
    file << "public:\n";
    file << "    virtual ~" << baseName << "() = default;\n";
    file << "    template <typename R>\n";
    file << "    virtual R accept(Visitor<R>* visitor) const = 0;\n";
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

