#include "combinator.h"

#include "valueExpression.h"
#include "signals.h"
#include <sstream>

unsigned int Entity::GLOBAL_ENTITY_ID = 1;

Entity::Entity(std::string pName, float x, float y) :
    id(GLOBAL_ENTITY_ID++), prototypeName(pName), x(x), y(y){}

void Entity::setConst(int side, unsigned int value){
    inConst[side] = true;
    inSignal[side] = value;
}

ArithmeticCombinator::ArithmeticCombinator(const ValueExpression& ve): Entity("arithmetic-combinator"){
    outSignal = ve.getOutColor(NULL);
    inSignal[0] = ve.getInColor(LEFT);
    inSignal[1] = ve.getInColor(RIGHT);
}

std::string Entity::getConnectionString() const {
    std::stringstream ss;
    ss << esc("connections") << ":{";
    if(incomingRedConnections.size() > 0)
        ss << esc("1") << ":{" << esc("red") << ":[";
    
    for(size_t i=0; i<incomingRedConnections.size(); i++){
        ss << "{" <<
        esc("entity_id") << ":" << incomingRedConnections[i] << "," <<
        esc("circuit_id") << ":" << 2 <<
        "}";
        if(i+1 < incomingRedConnections.size()) ss << ",";
    }

    if(incomingRedConnections.size() > 0){
        ss << "]}";
        if(outgoingRedConnections.size() > 0)
            ss << ",";
    }

    if(outgoingRedConnections.size() > 0)
        ss << esc("2") << ":{" << esc("red") << ":[";

    for(size_t i=0; i<outgoingRedConnections.size(); i++){
        ss << "{" <<
        esc("entity_id") << ":" << outgoingRedConnections[i] << "," <<
        esc("circuit_id") << ":" << 1 <<
        "}";
        if(i+1 < outgoingRedConnections.size()) ss << ",";
    }

    if(outgoingRedConnections.size() > 0)
        ss << "]}";
    
    ss << "}";

    return ss.str();
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

std::string ArithmeticCombinator::toBlueprint() const {
    std::stringstream res;
    res << "{\"entity_number\":" << id << ',' <<
    "\"name\":" << esc(prototypeName) << ',' <<
    esc("position") << ":{" << 
    esc("x") << ":" << x << ',' <<
    esc("y") << ":" << y << "}," <<
    getControlString() << ',' <<
    getConnectionString() << "}";

    return res.str();
}
