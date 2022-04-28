#include "entity.h"
#include <sstream>
#include <cmath>
#include <map>
#include "signals.h"

using namespace factolog;

unsigned int Entity::GLOBAL_ENTITY_ID = 1;

Entity::Entity(std::string pName, int reach, float x, float y) :
    id(GLOBAL_ENTITY_ID++), prototypeName(pName), pos(x,y), reach(reach){}

void Entity::setConst(int side, unsigned int value){
    inConst[side] = true;
    inSignal[side] = value;
}

void Entity::addIncomingConnection(EID from, bool red){
    if(red)
        incomingRedConnections.push_back(from);
    else
        incomingGreenConnections.push_back(from);
}

void Entity::addOutgoingConnection(EID to, bool red){
    if(red)
        outgoingRedConnections.push_back(to);
    else
        outgoingGreenConnections.push_back(to);
}

std::string Entity::getConnectionString() const {
    std::stringstream ss;
    ss << esc("connections") << ":{" <<
    esc("1") << ":{" <<
    esc("red") << ":[";

    //Print red connections
    for(size_t i=0; i<incomingRedConnections.size(); i++){
        ss << "{" <<
        esc("entity_id") << ":" << incomingRedConnections[i] << "," <<
        esc("circuit_id") << ":" << 2 <<
        "}";
        if(i+1 < incomingRedConnections.size()) ss << ",";
    }

    ss << "]," << 
    esc("green") << ":[";

    //Print green connections
    for(size_t i=0; i<incomingGreenConnections.size(); i++){
        ss << "{" <<
        esc("entity_id") << ":" << incomingGreenConnections[i] << "," <<
        esc("circuit_id") << ":" << 2 <<
        "}";
        if(i+1 < incomingGreenConnections.size()) ss << ",";
    }

    ss << "]},";

    ss << esc("2") << ":{" <<
    esc("red") << ":[";

    //Print red connections
    for(size_t i=0; i<outgoingRedConnections.size(); i++){
        ss << "{" <<
        esc("entity_id") << ":" << outgoingRedConnections[i] << "," <<
        esc("circuit_id") << ":" << 1 <<
        "}";
        if(i+1 < outgoingRedConnections.size()) ss << ",";
    }

    ss << "]," << 
    esc("green") << ":[";

    //Print green connections
    for(size_t i=0; i<outgoingGreenConnections.size(); i++){
        ss << "{" <<
        esc("entity_id") << ":" << outgoingGreenConnections[i] << "," <<
        esc("circuit_id") << ":" << 1 <<
        "}";
        if(i+1 < outgoingGreenConnections.size()) ss << ",";
    }

    ss << "]}}";

    return ss.str();
}

float Entity::distanceTo(const Entity& e) const{
    float dX = std::pow(pos.x-e.pos.x, 2);
    float dY = std::pow(pos.y-e.pos.y, 2);
    return std::sqrt(dX+dY);
}

bool Entity::checkConnections(const std::map<EID, Entity*>& entities) const{
    return
        checkConnections(entities, incomingRedConnections) &&
        checkConnections(entities, outgoingRedConnections) &&
        checkConnections(entities, incomingGreenConnections) &&
        checkConnections(entities, outgoingGreenConnections);
}

bool Entity::checkConnections(const std::map<EID, Entity*>& entities, const std::vector<EID>& conns) const{
    for(size_t i=0; i<conns.size(); i++)
        if(distanceTo(*entities.at(conns[i])) >= 12) return false;
    
    return true;
}

int Entity::connections() const {
    return 
        incomingRedConnections.size() +
        outgoingRedConnections.size() +
        incomingGreenConnections.size() +
        outgoingGreenConnections.size();
}

Position Entity::getDesiredPosition(const std::map<EID, Entity*>& entities) const{
    std::vector<EID> conns[] = {
        incomingRedConnections,
        outgoingRedConnections,
        incomingGreenConnections,
        outgoingGreenConnections
    };

    Position desired(0,0);
    int numConns = 0;

    for(size_t i=0; i<4; i++){
        for(size_t ii=0; ii<conns[i].size(); ii++){
            desired += entities.at(conns[i][ii])->getPosition();
            numConns++;
        }
    }

    return numConns != 0 ? desired/numConns : desired;
}
