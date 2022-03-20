#ifndef lexemes_H
#define lexemes_H

#include "matcher.h"

#include "treenode.h"

class Lexer;


class Expression : public TreeNode {
    public:
    enum BinaryOperator {
        PLUS, MINUS, AND, OR, XOR, 
        MUL, DIV, MOD, LSHIFT, RSHIFT,
        EXPONENT
    };

    protected:
    Expression* left;
    Expression* right;
    
    public:
    enum BinaryOperator op;
    static Expression* parse(Lexer&);
};

class Term : public Expression {
    /*private:
    Term* left;
    Term* right;*/
    public:
    static Term* parse(Lexer&);
};

class Factor : public Expression {
    /*private:
    Factor* left;
    Factor* right;*/
    public:
    static Factor* parse(Lexer&);
};

class UnaryExpression : public Expression {
    public:
    enum Operator {PLUS, MINUS, NOT};
    static UnaryExpression* parse(Lexer&);
    enum Operator op;
    TreeNode *expr;   ///< Kifejezés, amire alkalmazni kell az operátort
    UnaryExpression():Expression(){op=PLUS;};
};

class Value : public TreeNode {
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