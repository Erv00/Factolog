#include "combinator.h"

#include "valueExpression.h"
#include "signals.h"
#include <sstream>

unsigned int Combinator::GLOBAL_ENTITY_ID = 1;

Combinator::Combinator(std::string pName, float x, float y) :
    id(GLOBAL_ENTITY_ID++), prototypeName(pName), x(x), y(y){}

void Combinator::setConst(int side, unsigned int value){
    inConst[side] = true;
    inSignal[side] = value;
}

ArithmeticCombinator::ArithmeticCombinator(const ValueExpression& ve): Combinator("arithmetic-combinator"){
    //outSignal = ve.getOutColor();
    outSignal = 26;
    inSignal[0] = ve.getInColor(LEFT);
    inSignal[1] = ve.getInColor(RIGHT);
}

/*
{"entity_number":1,"name":"substation","position":{"x":12,"y":-3},
"connections":{"1":{"red":[{"entity_id":2,"circuit_id":2}]}}}

{"entity_number":2,"name":"arithmetic-combinator","position":{"x":16.5,"y":-2},
"control_behavior":{"arithmetic_conditions":{
    "first_signal":{"type":"virtual","name":"signal-A"},
    "second_signal":{"type":"virtual","name":"signal-B"},
    "operation":"+",
    "output_signal":{"type":"virtual","name":"signal-A"}}
    },
"connections":{"2":{"red":[{"entity_id":1}]}}}

*/

std::string Combinator::getConnectionString() const {
    std::stringstream ss;
    ss << esc("connections") << ":{";
    if(incomingConnections.size() > 0)
        ss << esc("1") << ":{" << esc("red") << ":[";
    
    for(size_t i=0; i<incomingConnections.size(); i++){
        ss << "{" <<
        esc("entity_id") << ":" << incomingConnections[i] << "," <<
        esc("circuit_id") << ":" << 2 <<
        "}";
    }

    if(incomingConnections.size() > 0){
        ss << "]}";
        if(outgoingConnections.size() > 0)
            ss << ",";
    }

    if(outgoingConnections.size() > 0)
        ss << esc("2") << ":{" << esc("red") << ":[";

    for(size_t i=0; i<outgoingConnections.size(); i++){
        ss << "{" <<
        esc("entity_id") << ":" << outgoingConnections[i] << "," <<
        esc("circuit_id") << ":" << 1 <<
        "}";
    }

    if(outgoingConnections.size() > 0)
        ss << "]}";
    
    ss << "}";

    return ss.str();
}

std::string Combinator::getControlString() const {
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

std::string ArithmeticCombinator::toBlueprint() const {
    std::stringstream res;
    res << "{\"entity_number\":" << id << ',' <<
    "\"name\":" << esc(prototypeName) << ',' <<
    esc("direction") << ":" << 4 << ',' <<
    esc("position") << ":{" << 
    esc("x") << ":" << x << ',' <<
    esc("y") << ":" << y << "}," <<
    getControlString() << ',' <<
    getConnectionString() << "}";

    return res.str();
}
