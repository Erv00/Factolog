#ifndef lexemes_H
#define lexemes_H

#include "matcher.h"

#include "treenode.h"


std::ostream& dotConnection(std::ostream& os, const void *from, const void *to);


class Lexer;

class ValueExpression : public TreeNode {
    public:
    virtual ~ValueExpression(){};
}; 

class BinaryExpression : public ValueExpression {
    protected:
    ValueExpression* left;
    ValueExpression* right;
    public:
    BinaryExpression():left(NULL),right(NULL){}
    virtual ~BinaryExpression(){};
};

class Expression : public BinaryExpression {
    public:
    enum BinaryOperator {
        PLUS, MINUS, AND, OR, XOR
    };

    public:
    ~Expression(){};
    enum BinaryOperator op;
    static ValueExpression* parse(Lexer&);
    std::ostream& printDot(std::ostream& os) const;
};

class Term : public BinaryExpression {
    public:
    ~Term(){};
    enum BinaryOperator {
        MUL, DIV, MOD, LSHIFT, RSHIFT
    };
    enum BinaryOperator op;
    static ValueExpression* parse(Lexer&);
    std::ostream& printDot(std::ostream& os) const;
};

class Factor : public BinaryExpression {
    public:
    ~Factor(){};
    static ValueExpression* parse(Lexer&);
    std::ostream& printDot(std::ostream& os) const;
};

class UnaryExpression : public ValueExpression {
    public:
    ~UnaryExpression(){};
    enum Operator {PLUS, MINUS, NOT};
    static ValueExpression* parse(Lexer&);
    enum Operator op;
    ValueExpression *expr;   ///< Kifejezés, amire alkalmazni kell az operátort
    UnaryExpression(){op=PLUS;};
    std::ostream& printDot(std::ostream& os) const;
};

class Value : public ValueExpression {
    public:
    virtual ~Value(){};
    static Value* parse(Lexer& l);
};

class Number : public Value {
    int value;
    Number(int val):value(val){};
    public:
    ~Number(){};
    static Number* parse(Lexer &l);
    std::ostream& printDot(std::ostream& os) const;
};

class Identifier : public Value{
    std::string name;
    Identifier(std::string name):name(name){};
    public:
    ~Identifier(){};
    static Identifier* parse(Lexer& l);
    std::ostream& printDot(std::ostream& os) const;
};
#endif //lexemes_H