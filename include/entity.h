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
#ifndef entity_H
#define entity_H

#include <string>
#include <vector>
#include <memtrace.h>

typedef unsigned int EID;
class ValueExpression;

class Entity {
    protected:
    EID id;
    std::string prototypeName;
    float x,y;
    unsigned int outSignal;
    unsigned int inSignal[2];
    bool         inConst[2];

    std::vector<EID> outgoingRedConnections;
    std::vector<EID> incomingRedConnections;

    static unsigned int GLOBAL_ENTITY_ID;

    public:
    Entity(std::string pName, float x = 0, float y = 0);
    virtual ~Entity(){}

    void setConst(int side, unsigned int value);
    void setPos(float nX, float nY){x=nX; y=nY;}

    void addIncomingConnection(EID from){incomingRedConnections.push_back(from);}
    void addOutgoingConnection(EID to){outgoingRedConnections.push_back(to);}

    EID getEID() const {return id;}

    static void resetGlobalID() {GLOBAL_ENTITY_ID = 1;}

    virtual std::string getConnectionString() const;
    virtual std::string toBlueprint() const = 0;
};


#endif //entity_H
