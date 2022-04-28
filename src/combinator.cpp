#include "combinator.h"

#include <sstream>
#include "signals.h"

using namespace factolog;


std::string Combinator::toBlueprint() const {
    std::stringstream res;
    res << "{\"entity_number\":" << id << ',' <<
    "\"name\":" << esc(prototypeName) << ',' <<
    esc("position") << ":{" << 
    esc("x") << ":" << pos.x << ',' <<
    esc("y") << ":" << pos.y << "}," <<
    getControlString() << ',' <<
    getConnectionString() << "}";

    return res.str();
}
