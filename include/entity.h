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

#include <cmath>
#include <string>
#include <vector>
#include <memtrace.h>

#include "connection.h"
#include "position.h"

class ValueExpression;


class Entity {
    protected:
    EID id;
    std::string prototypeName;
    Position pos;
    unsigned int outSignal;
    unsigned int inSignal[2];
    bool         inConst[2];
    const int reach;

    std::vector<EID> outgoingRedConnections;
    std::vector<EID> incomingRedConnections;
    std::vector<EID> outgoingGreenConnections;
    std::vector<EID> incomingGreenConnections;

    static unsigned int GLOBAL_ENTITY_ID;

    public:
    Entity(std::string pName, int reach, float x = 0, float y = 0);
    virtual ~Entity(){}

    void setConst(int side, unsigned int value);
    void setPos(float nX, float nY){pos.x=nX; pos.y=nY;}
    void setPos(const Position& p){setPos(p.x,p.y);}

    void addIncomingConnection(EID from, bool red=true);//{incomingRedConnections.push_back(from);}
    void addOutgoingConnection(EID to, bool red=true);//{outgoingRedConnections.push_back(to);}

    EID getEID() const {return id;}
    int getReach() const{return reach;}
    Position& getPosition() {return pos;}
    const Position& getPosition() const {return pos;}

    static void resetGlobalID() {GLOBAL_ENTITY_ID = 1;}

    virtual std::string getConnectionString() const;
    virtual std::string toBlueprint() const = 0;

    bool checkConnections(const std::map<EID, Entity*>& entities) const;
    bool checkConnections(const std::map<EID, Entity*>& entities, const std::vector<EID>& conns) const;
    Position getDesiredPosition(const std::map<EID, Entity*>& entities) const;
    float distanceTo(const Entity& e) const;
    int connections() const;
};


#endif //entity_H
