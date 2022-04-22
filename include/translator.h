/**
 * @file translator.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Identifier fordító
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef translator_H
#define translator_H

#include <map>

#include <memtrace.h>

#include "identifier.h"

/**
 * @brief Identifier fordító
 * 
 * Modulok összeköttetésénél a hívó paraméternevei és a hívott paraméternevei közötti fordítást végzi.
 */
class Translator {
    std::map<Identifier, Identifier> trans; ///< Név-összerendelések
    unsigned int translationID;             ///< Modulok lokális változóinak egyedisége

    static unsigned int globalTranslationID;///< Többszintű fordítás esetén a változónevek egyediségét garantálja

    public:
    /**
     * @brief Új Translator létrehozása
     * 
     * @param tr A név-összerendelések
     */
    Translator(const std::map<Identifier, Identifier>& tr):trans(tr),translationID(globalTranslationID++){}

    /**
     * @brief Összerendelés lekérdezés
     * 
     * @param id A lekérdezendő azonosító
     * @return Identifier Az annak megfelelő azonosító
     */
    Identifier at(const Identifier& id) const;    
};

#endif //translator_H
