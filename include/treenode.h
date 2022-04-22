/**
 * @file treenode.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief AST alapja
 * @version 0.1
 * @date 2022-03-24
 * @sa @ref AST
 * @copyright Copyright (c) 2022
 */
#ifndef treenode_H
#define treenode_H

#include <iostream>
#include <memtrace.h>
#include "combinator.h"


class Blueprint;
class CompilationUnit;

/**
 * @brief AST alaposztály
 */
class TreeNode{
public:
    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    virtual std::ostream& printDot(std::ostream& os) const = 0;

    /**
     * @brief Szemantika ellenőrzést végez
     * 
     * Minden nyelvi elemnek sajátos ellenőrzése lehet. 
     * Az olyan elemeknek, amelek nem igényelnek különleges ellenőrzést, 
     * az alapértelmezett implementáció nem csinál semmit
     * 
     * @param cu Az adott fordítási egység
     */
    virtual void checkSemantics(CompilationUnit& cu) const{(void)cu;};

    /**
     * @brief TreeNode felszabadítása
     */
    virtual ~TreeNode(){};

    /**
     * @brief TreeNode hozzáadása blueprinthez
     * 
     * @param bp A tervrajz
     * @return EID A hozááadott elem azonosítója, vagy 0
     */
    virtual EID addToBlueprint(Blueprint& bp) const {return 0;}
};

#endif //treenode_H
