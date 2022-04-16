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
    std::string name;

    std::map<EID, Combinator*> combinators;

    float x, y;

    public:
    Blueprint(const unsigned int reach, const unsigned int dim, const Module* module);
    ~Blueprint();
    
    /**
     * @brief Kapcsolatot teremt két kombinátor között
     * 
     * @param from A kimeneti kombinátor, vagy 0 a buszhoz 
     * @param to A bementei kombinátor, vagy 0 a buszhoz
     */
    void connect(EID from, EID to);

    EID addCombinator(Combinator *c);

    void openColumn(){y=0;x++;}

    //void expand(char direction);
    const std::map<EID, Combinator*>& getCombinators() const {return combinators;}
    std::string getName() const {return name;}
};

std::ostream& operator<<(std::ostream& os, const Blueprint& bp);

#endif //blueprint_H
