/**
 * @file combinator.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Kombinátorok
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef combinator_H
#define combinator_H

#include <string>
#include <vector>
#include <memtrace.h>

typedef unsigned int EID;
class ValueExpression;

class Combinator {
    protected:
    EID id;
    std::string prototypeName;
    float x,y;
    unsigned int outSignal;
    unsigned int inSignal[2];
    bool         inConst[2];

    std::vector<EID> outgoingConnections;
    std::vector<EID> incomingConnections;

    static unsigned int GLOBAL_ENTITY_ID;

    public:
    Combinator(std::string pName, float x = 0, float y = 0);
    virtual ~Combinator(){}

    void setConst(int side, unsigned int value);
    void setPos(float nX, float nY){x=nX; y=nY;}

    void addIncomingConnection(EID from){incomingConnections.push_back(from);}
    void addOutgoingConnection(EID to){outgoingConnections.push_back(to);}

    EID getEID() const {return id;}

    static void resetGlobalID() {GLOBAL_ENTITY_ID = 1;}

    std::string getConnectionString() const;
    std::string getControlString() const;
    virtual std::string getOperationString() const = 0;
    virtual std::string toBlueprint() const = 0;
};

class ArithmeticCombinator : public Combinator {
    public:
    enum Operation {PLUS, MINUS, MUL, DIV, MOD, EXP, LSHIFT, RSHIFT, AND, OR, XOR};

    Operation op;

    ArithmeticCombinator();
    ArithmeticCombinator(const ValueExpression& ve);
    ArithmeticCombinator(Operation op);

    std::string getOperationString() const;
    std::string toBlueprint() const;
};

#endif //combinator_H
