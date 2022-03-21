#ifndef lexemes_H
#define lexemes_H

#include "matcher.h"

#include "treenode.h"

class Lexer;

class ValueExpression : public TreeNode {
    protected:
    ValueExpression* left;
    ValueExpression* right;
}; 

class Expression : public ValueExpression {
    public:
    enum BinaryOperator {
        PLUS, MINUS, AND, OR, XOR
    };

    public:
    enum BinaryOperator op;
    static ValueExpression* parse(Lexer&);
};

class Term : public ValueExpression {
    public:
    enum BinaryOperator {
        MUL, DIV, MOD, LSHIFT, RSHIFT
    };
    enum BinaryOperator op;
    static ValueExpression* parse(Lexer&);
};

class Factor : public ValueExpression {
    public:
    static ValueExpression* parse(Lexer&);
};

class UnaryExpression : public ValueExpression {
    public:
    enum Operator {PLUS, MINUS, NOT};
    static ValueExpression* parse(Lexer&);
    enum Operator op;
    ValueExpression *expr;   ///< Kifejezés, amire alkalmazni kell az operátort
    UnaryExpression(){op=PLUS;};
};

class Value : public ValueExpression {
    public:
    static Value* parse(Lexer& l);
};

class Number : public Value {
    int value;
    Number(int val):value(val){};
    public:
    static Number* parse(Lexer &l);
};

class Identifier : public Value{
    std::string name;
    Identifier(std::string name):name(name){};
    public:
    static Identifier* parse(Lexer& l);
};
#endif //lexemes_H