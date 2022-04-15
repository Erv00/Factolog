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

class Identifier;

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
    virtual void translate(const std::map<Identifier,Identifier>& translation) = 0;
};


#endif //asyncExpression_H
