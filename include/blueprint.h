/**
 * @file blueprint.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Factorio tervrajz
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef blueprint_H
#define blueprint_H

#include "modules.h"
#include <string>
#include <map>
#include <vector>
#include "combinator.h"

class Blueprint {
    const unsigned int POLE_REACH;
    const unsigned int POLE_DIM;
    const std::string POLE_NAME;
    std::string name;

    std::map<EID, Entity*> entities;
    Entity **area;

    float x, y;

    public:
    Blueprint(const unsigned int reach, const unsigned int dim, const std::string poleName, const Module* module);
    ~Blueprint();
    
    /**
     * @brief Kapcsolatot teremt két kombinátor között
     * 
     * @param from A kimeneti kombinátor, vagy 0 a buszhoz 
     * @param to A bementei kombinátor, vagy 0 a buszhoz
     */
    void connect(EID from, EID to);

    EID addEntity(Entity *c);
    EID addEntity(Entity *e, float x, float y);
    void moveEntity(Entity *e, const Position& newPos);

    void openColumn(){y=0;x++;}
    Position getOpenPositionNear(const Position& pos, float maxDist, int ignore=0) const;

    //void expand(char direction);
    const std::map<EID, Entity*>& getEntities() const {return entities;}
    std::string getName() const {return name;}

    Entity*& at(const Position& pos);
    Entity* const & at(const Position& pos) const;
    bool canCombinatorFit(const Position& pos) const;

    void printArea(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const Blueprint& bp);

#endif //blueprint_H
