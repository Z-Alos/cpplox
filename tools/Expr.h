#pragma once

#include "../src/Token/Token.h"
#include <variant>
#include <string>
using Object = std::variant<std::monostate, double, std::string, bool>;

class Binary;
class Grouping;
class Literal;
class Unary;

struct Visitor {
    virtual void visitBinaryExpr(const Binary* Expr) = 0;
    virtual void visitGroupingExpr(const Grouping* Expr) = 0;
    virtual void visitLiteralExpr(const Literal* Expr) = 0;
    virtual void visitUnaryExpr(const Unary* Expr) = 0;
};

class Expr {
public:
    virtual ~Expr() = default;
    virtual void accept(Visitor* visitor) const = 0;
};

class Binary : public Expr {
public:
    Binary(Expr* left, Token operator_, Expr* right)
        : left(left), operator_(operator_), right(right) {}

    Expr* left;
    Token operator_;
    Expr* right;

    void accept(Visitor* visitor) const override {
        visitor->visitBinaryExpr(this);
    }
};

class Grouping : public Expr {
public:
    Grouping(Expr* expression)
        : expression(expression) {}

    Expr* expression;

    void accept(Visitor* visitor) const override {
        visitor->visitGroupingExpr(this);
    }
};

class Literal : public Expr {
public:
    Literal(Object value)
        : value(value) {}

    Object value;

    void accept(Visitor* visitor) const override {
        visitor->visitLiteralExpr(this);
    }
};

class Unary : public Expr {
public:
    Unary(Token operator_, Expr* right)
        : operator_(operator_), right(right) {}

    Token operator_;
    Expr* right;

    void accept(Visitor* visitor) const override {
        visitor->visitUnaryExpr(this);
    }
};

