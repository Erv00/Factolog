#include "blueprint.h"
#include "signals.h"

Blueprint::Blueprint(const unsigned int reach, const unsigned int dim, const Module* module) : POLE_REACH(reach), POLE_DIM(dim), x(0), y(0) {
    name = module->getIdentifier()->getName();
}

Blueprint::~Blueprint(){
    for(std::map<EID, Combinator*>::iterator it=combinators.begin(); it != combinators.end(); it++)
        delete it->second;
}

void Blueprint::connect(EID from, EID to){
    //std::cout << "Connecting " << from << " -> " << to << std::endl;
    if(from != 0)
        combinators.at(from)->addOutgoingConnection(to);
    if(to != 0)
        combinators.at(to)->addIncomingConnection(from);
}

EID Blueprint::addCombinator(Combinator *c){
    c->setPos(x,y-2);
    y-=2;
    combinators[c->getEID()] = c;
    return c->getEID();
}

std::ostream& operator<<(std::ostream& os, const Blueprint& bp){
    os << "{" <<
    esc("blueprint") << ":{" <<
    esc("item") << ":" << esc("blueprint") << "," <<
    esc("label") << ":" << esc(bp.getName()) << "," <<
    esc("version") << ":" << 281479275413505 << "," <<
    "\"icons\":[{\"signal\":{\"type\":\"item\",\"name\":\"advanced-circuit\"},\"index\":1}]," <<
    esc("entities") << ":[";
    for(std::map<EID, Combinator*>::const_iterator it = bp.getCombinators().begin(); it != bp.getCombinators().end();){
        os << it->second->toBlueprint();
        if(++it != bp.getCombinators().end()) os << ",";
    }
    return os << "]}}";
}
