/**
 * @file compilationUnit.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Egy fordítási egység
 * @version 0.1
 * @date 2022-03-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef compilationUnit_H
#define compilationUnit_H

#include <set>
#include <map>

#include "modules.h"
#include "identifier.h"

/**
 * @brief Egy fordítási egység
 * 
 * Egy fordítási egység tartalmazza az összes ismert modult.
 * Egy modulhoz egy fordítási egység tartozik.
 * A modulhoz tartozó fordítási egység tartalmazza a modulban definiált változókat.
 */
class CompilationUnit{
    std::set<Identifier> definedVariables;                      ///<Definiált(deklarált) változók
    std::set<Identifier> assignedVariables;                     ///<Értékkel rendelkező változók
    const std::map<const Identifier, Module*> definedModules;   ///<Definiált modulok

    public:
    /**
     * @brief Új CompilationUnit létrehozása
     * 
     * @param modules A definiált modulok listája
     */
    CompilationUnit(const std::map<const Identifier, Module*> modules): definedModules(modules){}

    /**
     * @brief Visszaadja, hogy az adott változó létezik-e
     * 
     * @param id A változó azonosítója
     * @return true Ha a változó létezik
     * @return false Egyébként
     */
    bool isVariableDefined(const Identifier* id) const;

    /**
     * @brief Létrehozza az adott változót
     * 
     * @param id A létrehozandó változó
     */
    void defineVariable(const Identifier* id);

    /**
     * @brief Visszaadja, hogy az adott változónak van-e már értéke
     * 
     * @param id A változó azonosítója
     * @return true Ha a változónak van már értéke
     * @return false Egyébként
     */
    bool isVariableAssigned(const Identifier* id) const;

    /**
     * @brief Megjelöl egy adott változót mint értékkel rendelkező változó
     * 
     * @param id A változó azonosítója
     */
    void assignVariable(const Identifier* id);

    /**
     * @brief Visszaadja, hogy az adott modul definiálva van-e
     * 
     * @param module A modul azonosítója
     * @return true Ha a modul definiálva van
     * @return false Egyébként
     */
    bool isModuleDefined(const Identifier* module) const;

    /**
     * @brief Visszaadja a megadott modul paraméterlistáját
     * 
     * @param module A modul azonosítója
     * @return const ParameterListDeclaration* A modul paraméterlistája
     */
    const ParameterListDeclaration* getModuleParameters(const Identifier* module) const;
};

#endif //compilationUnit_H
