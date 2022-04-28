#include "constantCombinator.h"

#include "signals.h"
#include <sstream>

using namespace factolog;

ConstantCombinator::ConstantCombinator(Color sig, unsigned int val):Combinator("constant-combinator",11){
    signals[sig] = val;
}

std::string ConstantCombinator::getControlString() const {
    std::stringstream ss;
    ss << esc("control_behavior") << ":{" <<
    esc("filters") << ":[";

    int idx = 1;

    for(std::map<Color, unsigned int>::const_iterator it=signals.begin(); it != signals.end();){
        ss << "{" <<
        esc("signal") << ":{" <<
        esc("type") << ":" << esc(it->first.getType()) << "," <<
        esc("name") << ":\"" << it->first << "\"}," <<
        esc("count") << ":" << it->second << "," <<
        esc("index") << ":" << idx++ << "}";
        if(++it != signals.end()) ss << ",";
    }

    ss << "]}";

    return ss.str();
}

std::string ConstantCombinator::getConnectionString() const {
    std::stringstream ss;
    ss << esc("connections") << ":{" <<
    esc("1") << ":{" <<
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
