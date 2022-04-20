#include "pole.h"
#include "signals.h"
#include <sstream>

Pole::Pole(std::string pName, int reach):Entity(pName, reach){}

std::string Pole::getConnectionString() const{
    std::stringstream ss;
    ss << esc("connections") << ":{";
    if(incomingGreenConnections.size() > 0)
        ss << esc("1") << ":{" << esc("green") << ":[";
    
    for(size_t i=0; i<incomingGreenConnections.size(); i++){
        ss << "{" <<
        esc("entity_id") << ":" << incomingGreenConnections[i] << "," <<
        esc("circuit_id") << ":" << 2 <<
        "}";
        if(i+1 < incomingGreenConnections.size()) ss << ",";
    }

    if(incomingGreenConnections.size() > 0)
        if(outgoingGreenConnections.size() > 0)
            ss << ",";

    for(size_t i=0; i<outgoingGreenConnections.size(); i++){
        ss << "{" <<
        esc("entity_id") << ":" << outgoingGreenConnections[i] << "," <<
        esc("circuit_id") << ":" << 1 <<
        "}";
        if(i+1 < outgoingGreenConnections.size()) ss << ",";
    }

    if(outgoingGreenConnections.size() > 0)
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
    esc("x") << ":" << pos.x << "," <<
    esc("y") << ":" << pos.y << "}," <<
    getConnectionString() << "}";

    return ss.str();
}
