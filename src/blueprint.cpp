#include "blueprint.h"
#include "signals.h"
#include "pole.h"

Blueprint::Blueprint(const unsigned int reach, const unsigned int dim, const std::string poleName, const Module* module) : POLE_REACH(reach), POLE_DIM(dim), POLE_NAME(poleName), x(0), y(0) {
    name = module->getIdentifier()->getName();
    Pole *pole = new Pole(POLE_NAME);
    float pos = (reach-dim)/2;
    addEntity(pole, pos, pos);
}

Blueprint::~Blueprint(){
    for(std::map<EID, Entity*>::iterator it=entities.begin(); it != entities.end(); it++)
        delete it->second;
}

void Blueprint::connect(EID from, EID to){
    //std::cerr << "Connecting " << from << " -> " << to << std::endl;
    if(from != 0)
        entities.at(from)->addOutgoingConnection(to);
    else{
        //Connecting from bus
        //Get nearest pole
        entities.at(1)->addOutgoingConnection(to);
    }
    if(to != 0)
        entities.at(to)->addIncomingConnection(from);
    else{
        //Connecting to bus
        //Get nearest pole
        entities.at(1)->addIncomingConnection(from);
    }
}

EID Blueprint::addEntity(Entity *c){
    addEntity(c, x, y);
    y+=2;
    return c->getEID();
}

EID Blueprint::addEntity(Entity *c, float _x, float _y){
    c->setPos(_x,_y);
    entities[c->getEID()] = c;
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
    for(std::map<EID, Entity*>::const_iterator it = bp.getEntities().begin(); it != bp.getEntities().end();){
        os << it->second->toBlueprint();
        if(++it != bp.getEntities().end()) os << ",";
    }
    return os << "]}}";
}
