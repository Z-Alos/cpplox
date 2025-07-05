#pragma once

#include "../src/Token/Token.h";

using Object = std::variant<std::monostate, double, std::string, bool>;

class Expr {
public:
    virtual ~Expr() = default;
};

class Binary : public Expr {
public:
    Binary(Expr* left, Token operator, Expr* right)Expr* left, Token operator_, Expr* right {}

    Expr* left;
    Token operator_;
    Expr* right;
};

class Grouping : public Expr {
public:
    Grouping(Expr* expression)Expr* expression {}

    Expr* expression;
};

class Literal : public Expr {
public:
    Literal(Object value)Object value {}

    Object value;
};

class Unary : public Expr {
public:
    Unary(Token operator, Expr* right)Token operator_, Expr* right {}

    Token operator_;
    Expr* right;
};

