#ifndef lexemes_H
#define lexemes_H

#include <vector>

#include "treenode.h"
#include "lexer.h"

#include <memtrace.h>

class AsyncExpression;
class ParameterListDeclaration;
class ParameterList;

std::ostream& dotConnection(std::ostream& os, const void *from, const void *to);
std::ostream& dotNode(std::ostream& os, const void *obj, const char *label, const char *style);

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
    virtual ~BinaryExpression(){
        delete left;
        delete right;
    };
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
    ~UnaryExpression(){delete expr;};
    enum Operator {PLUS, MINUS, NOT};
    static ValueExpression* parse(Lexer&);
    enum Operator op;
    ValueExpression *expr;   ///< Kifejezés, amire alkalmazni kell az operátort
    UnaryExpression(){op=PLUS;expr=NULL;};
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
    std::string& getName(){return name;};
};

class AsyncExpression : public TreeNode {
    public:
    ~AsyncExpression(){};
    static AsyncExpression* parse(Lexer& l);
};
class VariableDeclaration : public AsyncExpression {
    std::vector<Identifier*> varsDeclared;
    public:
    ~VariableDeclaration(){
        for(size_t i=0; i<varsDeclared.size(); i++)
            delete varsDeclared[i];
    }
    static VariableDeclaration* parse(Lexer& l);
    std::ostream& printDot(std::ostream& os) const;
};
class Assignment : public AsyncExpression {
    Identifier *to;
    ValueExpression *val;
    public:
    ~Assignment(){delete to; delete val;};
    static Assignment* parse(Lexer& l);
    std::ostream& printDot(std::ostream& os) const;
};
class Parameter : public TreeNode {
    public:
    enum Direction {IN, OUT};
    private:
    enum Direction direction;
    Identifier* identifier;
    public:
    ~Parameter(){delete identifier;};
    static Parameter* parse(Lexer& l);
    std::ostream& printDot(std::ostream& os) const;
};
class ParameterList : public TreeNode {
    std::vector<ValueExpression*> parameters;    ///< Paraméterek nevei
    public:
    ~ParameterList(){
        for(size_t i=0; i<parameters.size(); i++)
            delete parameters[i];
    };
    static ParameterList* parse(Lexer& l);
    std::ostream& printDot(std::ostream& os) const;
};
class ParameterListDeclaration : public TreeNode {
    std::vector<Parameter*> parameters;
    public:
    ~ParameterListDeclaration(){
        for(size_t i=0; i<parameters.size(); i++)
            delete parameters[i];
    }
    static ParameterListDeclaration* parse(Lexer& l);
    std::ostream& printDot(std::ostream& os) const;
};
class Module : public TreeNode {
    protected:
    Identifier* identifier;
    ParameterListDeclaration* parameters;
    public:
    ~Module(){delete identifier;delete parameters;};
};
class AsyncModule : public Module {
    std::vector<AsyncExpression*> expressions;
    public:
    ~AsyncModule(){
        for(size_t i=0; i<expressions.size(); i++)
            delete expressions[i];
    };
    static AsyncModule* parse(Lexer& l);
    std::ostream& printDot(std::ostream& os) const;
};
class ModuleConnection : public AsyncExpression {
    Identifier *identifier;
    ParameterList *parameters;
    public:
    ~ModuleConnection(){delete identifier; delete parameters;};
    static ModuleConnection* parse(Lexer& l);
    std::ostream& printDot(std::ostream& os) const;
};
#endif //lexemes_H
