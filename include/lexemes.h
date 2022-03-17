#ifndef lexemes_H
#define lexemes_H

#include "matcher.h"

class Lexer;

class Identifier : Matcher{
    public:
    Identifier(Lexer&);
    bool match();
};

class ValueExpression : Matcher {
    public:
    ValueExpression(Lexer&);
};

class Term : Matcher {
    public:
    Term(Lexer&);
};

class Factor : Matcher {
    public:
    Factor(Lexer&);
};

class Exponent : Matcher {
    public:
    Exponent(Lexer&);
};

class UnaryOperator : Matcher {
    public:
    UnaryOperator(Lexer&);
};

class Value : protected Matcher {
    public:
    Value(Lexer&);
};

class Number : protected Value {
    int value;
    public:
    Number(Lexer&);
};

#endif //lexemes_H