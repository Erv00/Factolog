#ifndef combinator_H
#define combinator_H

#include "entity.h"

class ArithmeticCombinator : public Entity {
    public:
    enum Operation {PLUS, MINUS, MUL, DIV, MOD, EXP, LSHIFT, RSHIFT, AND, OR, XOR};

    Operation op;

    ArithmeticCombinator();
    ArithmeticCombinator(const ValueExpression& ve);
    ArithmeticCombinator(Operation op);

    std::string getControlString() const;
    std::string getOperationString() const;
    std::string toBlueprint() const;
};

#endif //combinator_H