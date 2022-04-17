#include "pole.h"
#include "signals.h"
#include <sstream>

Pole::Pole(std::string pName):Entity(pName){}

std::string Pole::getConnectionString() const{
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

    if(incomingRedConnections.size() > 0)
        if(outgoingRedConnections.size() > 0)
            ss << ",";

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

std::string Pole::toBlueprint() const {
    std::stringstream ss;
    ss << "{" <<
    esc("entity_number") << ":" << id << ',' <<
    esc("name") << ":" << esc(prototypeName) << ',' <<
    esc("position") << ":{" <<
    esc("x") << ":" << x << "," <<
    esc("y") << ":" << y << "}," <<
    getConnectionString() << "}";

    return ss.str();
}
