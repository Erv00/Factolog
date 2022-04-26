/**
 * @file linkingUnit.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Linkelési (színezési) egység
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef linkingUnit_H
#define linkingUnit_H

#include <map>

#include "identifier.h"
#include <memtrace.h>

/**
 * @brief Linkelési (színezési) egység
 * 
 * Tartalmazza a változók színeit
 * 
 */
class LinkingUnit{
    std::map<const Identifier, Color> variableColors;    ///< A változók színei

    public:
    /**
     * @brief Új LinkingUnit létrehozása
     * 
     * @tparam RandomIt Iterátor típus
     * @param firstID Iterátor az első változó nevére (Identifier)
     * @param lastID Iterátor az utolsó utáni változó nevére (Identifier)
     */
    template<class RandomIt>
    LinkingUnit(RandomIt firstID, RandomIt lastID){
        Color color = 3; //First 3 are reserved
        for(;firstID != lastID; firstID++)
            variableColors[*firstID] = color++;
    }

    /**
     * @brief Új LinkingUnit létrehozása
     * 
     * @tparam IDIt Identifier iterátor
     * @tparam ColorIt Szín iterátor
     * @param firstID Iterátor az első változó nevére (Identifier)
     * @param lastID Iterátor az utolsó utáni változó nevére (Identifier)
     * @param firstColor Iterátor az első színre
     * @param lastColor Iterátor az utolsó utáni színre
     */
    template<class IDIt, class ColorIt>
    LinkingUnit(IDIt firstID, IDIt lastID, ColorIt firstColor, ColorIt lastColor){
        while(firstID != lastID && firstColor != lastColor){
            variableColors[*firstID] = *firstColor;
            firstID++;
            firstColor++;
        }
    }

    /**
     * @brief Visszaadja egy változó színét
     * 
     * @param id A változó azonosítója
     * @return Color A változó színe
     */
    Color getVariableColor(const Identifier& id) const;

    /**
     * @brief Megadja, hogy egy adott változónak van-e színe
     * 
     * @param id A változó azonosítója 
     * @return true Ha a változónak van színe
     * @return false Egyébként
     */
    bool variableHasColor(const Identifier& id) const;

    /**
     * @brief Változó-jelszín asszociációk kiírása debug célból.
     * 
     * @param os A kimeneti stream
     */
    void printVariableColorAssociation(std::ostream& os) const;
};

#endif //linkingUnit_H
