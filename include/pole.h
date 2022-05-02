/**
 * @file pole.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Tápok
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef pole_H
#define pole_H

#include "entity.h"
#include "memtrace.h"

namespace factolog {

/**
 * @brief Táp
 * A táp szolgál a globális változótérként, és áramforrásként
 */
class Pole : public Entity{
    public:
    /**
     * @brief Új Pole létrehozása
     * 
     * @param pName A táp Factorio prototype neve
     * @param reach A táb lefedésének hossza
     */
    Pole(std::string pName, int reach);

    std::string getConnectionString() const;
    std::string toBlueprint() const;
};

} //namespace factolog

#endif //pole_H
