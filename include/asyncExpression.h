/**
 * @file asyncExpression.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Aszinkron kifejezés
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef asyncExpression_H
#define asyncExpression_H

#include "treenode.h"
#include "lexer.h"

#include <memtrace.h>

class Module;
class Identifier;
class Translator;
class LinkingUnit;
class AsyncModule;

/**
 * @brief Aszinkron kifejezés
 */
class AsyncExpression : public TreeNode {
    public:
    /**
     * @brief AsyncExpression felszabadítása
     */
    virtual ~AsyncExpression(){};

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return AsyncExpression* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static AsyncExpression* parse(Lexer& lex);

    /**
     * @brief Optimalizálja a kifejezést, ha ez lehetséges
     * 
     * Az alapértelmezett implementáció azt feltételezi, hogy nem lehet optimalizálni,
     *  így nem csinál semmit
     */
    virtual void optimize(){};

    /**
     * @brief Másolat létrehozása
     * 
     * A leszármaztatott másoló konstruktorát hívja
     * 
     * @return AsyncExpression* A dinamikusan foglalt másolat címe
     */
    virtual AsyncExpression* clone() const = 0;

    /**
     * @brief Lecseréli a változók azonosítóját a modulokban a kapcsolatban lévőkkel
     * 
     * @param translation Régi-új változónév összerendelések
     */
    virtual void translate(const Translator& translation) = 0;

    /**
     * @brief Elkészíti a szín-fát
     * 
     * Minen kombinátornak meghatározza a bemeneti és kimeneti színeit
     * Csak az Assignment osztálynak van rá szüksége, de az OOP miatt minden leszármaztatottnak kell.
     * Az alapértelmezett implementáció nem csinál semmit
     * 
     * @param lu Linkelési egység
     */
    virtual void calculateColorTree(LinkingUnit* lu){(void)lu;}

    /**
     * @brief Visszadja a modul linkelésekor keletkező kifejezéseket, fordítással
     * 
     * @param modules A definiált modulok
     * @param doDelete Referencia, igazra állítódik ha a meghívó listájában törölni kell az lemet, azaz kibontás történt
     * @return std::vector<AsyncExpression*> A linkeléskor keletkezett kifejezések listája
     */
    virtual std::vector<AsyncExpression*> linkExpression(const std::map<const Identifier, Module*>& modules, bool& doDelete){(void)modules; (void)doDelete; return std::vector<AsyncExpression*>();}
};


#endif //asyncExpression_H
