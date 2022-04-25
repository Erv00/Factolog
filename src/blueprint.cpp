#include "blueprint.h"
#include "signals.h"
#include "pole.h"
#include <queue>
#include <set>

Blueprint::Blueprint(const unsigned int reach, const unsigned int dim, const std::string poleName, const Module* module) : POLE_REACH(reach), POLE_DIM(dim), POLE_NAME(poleName), x(0), y(0) {
    name = module->getIdentifier()->getName();

    area = new Entity*[POLE_REACH*POLE_REACH];
    for(unsigned int i=0; i<POLE_REACH*POLE_REACH; i++)
        area[i] = NULL;

    Pole *pole = new Pole(POLE_NAME, POLE_REACH);
    float pos = (reach-dim)/2;
    addEntity(pole, pos, pos);
}

Blueprint::~Blueprint(){
    for(std::map<EID, Entity*>::iterator it=entities.begin(); it != entities.end(); it++)
        delete it->second;
    
    delete[] area;
}

void Blueprint::connect(EID from, EID to){
    bool red = !(from == 0 || to == 0);

    if(from == 0)
        //Get nearest pole
        from = 1;
    else if(to == 0)
        to = 1;
    

    Entity *fromE = entities.at(from);
    Entity *toE = entities.at(to);

    float dist = fromE->distanceTo(*toE);
    float maxDist = std::min(fromE->getReach(), toE->getReach());

    fromE->addOutgoingConnection(to, red);
    toE->addIncomingConnection(from, red);

    if(dist >= maxDist){
        //Connection too long
        //Try moving the one with de least connections
        Entity *toMove = fromE->connections() <= toE->connections() ? fromE : toE;

        //Get suitable position location
        Position desired = toMove->getDesiredPosition(entities);

        int ignore=0;

        do{
            //Move to next col
            Position candidate = getOpenPositionNear(desired, maxDist, ignore);
            ignore++;

            //Position oldPos = toMove->getPosition();

            //toMove->setPos(candidate);
            moveEntity(toMove, candidate);

        }while(!toMove->checkConnections(entities));
    }
}

EID Blueprint::addEntity(Entity *c){
    addEntity(c, x, y);
    y+=2;
    return c->getEID();
}

EID Blueprint::addEntity(Entity *c, float _x, float _y){
    if(_y >= POLE_REACH){
        //Put in next col and hope
        _y = 0;
        _x++;
        openColumn();
    }
    c->setPos(_x,_y);
    entities[c->getEID()] = c;

    //Rotation is hardcoded
    at(c->getPosition()) = c;
    at(c->getPosition()+Position(0,1)) = c;
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

Position Blueprint::getOpenPositionNear(const Position& pos, float maxDist, int ignore) const{
    //Do floodfill to get position near
    //Prefer up and right
    std::queue<Position> qu;
    std::set<Position> visited;
    qu.push(pos);
    visited.insert(pos);

    while(!qu.empty()){
        Position considering = qu.front();
        qu.pop();

        //visited.insert(considering);
        if(canCombinatorFit(considering)){
            if(ignore==0) return considering;
            else ignore--;
        }

        Position directions[] = {
            Position(+0,-1),    //Up
            Position(+1,+0),    //Right
            Position(-1,+0),    //Left
            Position(+0,+1)     //Down
        };

        for(int i=0; i<4; i++){
            Position next = considering+directions[i];
            if(next.inBounds(POLE_REACH)){
                if(pos.distanceTo(next) < maxDist){
                    if(visited.find(next) == visited.end()){
                        qu.push(next);
                        visited.insert(next);
                    }
                }
            }
        }
    }

    throw "No free space";

}

Entity*& Blueprint::at(const Position& pos){
    int idx = pos.y*POLE_REACH+pos.x;
    return area[idx];
}

Entity* const& Blueprint::at(const Position& pos) const {
    int idx = pos.y*POLE_REACH+pos.x;
    return area[idx];
}

void Blueprint::moveEntity(Entity *e, const Position& newPos){
    //Direction is hardcoded
    Position oldPos = e->getPosition();
    at(oldPos) = NULL;
    at(oldPos+Position(0,1)) = NULL;

    at(newPos) = e;
    at(newPos+Position(0,1)) = e;
    e->setPos(newPos);
}

bool Blueprint::canCombinatorFit(const Position& pos) const {
    return at(pos) == NULL && at(pos+Position(0,1)) == NULL;
}

void Blueprint::printArea(std::ostream& os) const {
    os << '#';
    for(unsigned int col=0; col<POLE_REACH; col++) os << "=";
    os << '#' << std::endl;

    for(unsigned int row=0; row<POLE_REACH; row++){
        os << '|';
        for(unsigned int col=0; col<POLE_REACH; col++){
            if(at(Position(col,row)) == NULL) os << ' ';
            else os << '#';
        }
        os << '|' << std::endl;
    }

    os << '#';
    for(unsigned int col=0; col<POLE_REACH; col++) os << "=";
    os << '#' << std::endl;
}
