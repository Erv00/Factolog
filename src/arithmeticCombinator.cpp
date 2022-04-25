#include "arithmeticCombinator.h"

#include "valueExpression.h"
#include "signals.h"
#include <sstream>

ArithmeticCombinator::ArithmeticCombinator(const ValueExpression& ve): Combinator("arithmetic-combinator", 12){
    outSignal = ve.getOutColor(NULL);
    inSignal[0] = ve.getInColor(LEFT);
    inSignal[1] = ve.getInColor(RIGHT);
}

std::string ArithmeticCombinator::getControlString() const {
    std::stringstream ss;
    ss << esc("control_behavior") << ":{" <<
    esc("arithmetic_conditions") << ":{" <<
    Signal<2>(inSignal, inConst) << ',' <<
    esc("operation") << ':' << getOperationString() << ',' <<
    Signal<1>(outSignal, false, true) << "}}";

    return ss.str();
}

std::string ArithmeticCombinator::getOperationString() const{
    switch(op){
        case PLUS:  return esc("+");
        case MINUS: return esc("-");
        case MUL:   return esc("*");
        case DIV:   return esc("/");
        case MOD:   return esc("%");
        case EXP:   return esc("^");
        case LSHIFT:return esc("<<");
        case RSHIFT:return esc(">>");
        case AND:   return esc("AND");
        case OR:    return esc("OR");
        case XOR:   return esc("XOR");
        default:    return esc("ERR");
    }
}
