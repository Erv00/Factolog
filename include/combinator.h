/**
 * @file combinator.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Factorio aritmetiaki kombinátor
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 * Ez a Factorio-ban létező aritmetikai kombinátort reprezentáló osztály
 * 
 */
#ifndef combinator_H
#define combinator_H

#include "entity.h"

#include "memtrace.h"

namespace factolog {

/**
 * @brief Kombinátor
 * 
 * Bementtel és/vagy kimenettel rendelkező elem.
 * A Factorioban található kombinátorok közös őse.
 * 
 */
class Combinator : public Entity {
    public:
    /**
     * @brief Új Entity létrehozása
     * 
     * @param pName Factorio prototípusnév
     * @param reach Összeköttetések maximum hossza
     * @param x X pozíció
     * @param y Y pozíció
     */
    Combinator(std::string pName, int reach, float x = 0, float y = 0):Entity(pName,reach,x,y){}

    /**
     * @brief "control_bahavior" meghatározása
     * 
     * @return std::string "control_behavior" JSON formában
     */
    virtual std::string getControlString() const = 0;

    std::string toBlueprint() const;
};

} //namespace factolog

#endif //combinator_H
