/**
 * @file binaryExpression.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief 2 operandusú műveletek
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef binaryExpression_H
#define binaryExpression_H

#include "valueExpression.h"

/**
 * @brief 2 operandusú műveletek base class-a
 */
class BinaryExpression : public ValueExpression {
    protected:
    ValueExpression* left;  ///<Bal oldal
    ValueExpression* right; ///<Jobb oldal

    public:
    /**
     * @brief Új BinaryExpression létrehozása
     */
    BinaryExpression():left(NULL),right(NULL){}
    
    /**
     * @brief BinaryExpression felszabadítása
     */
    virtual ~BinaryExpression(){
        delete left;
        delete right;
    };

    /**
     * @brief Szemantika ellenőrzést végez
     * 
     * Ellenőrzött tulajdonságok:
     * @li A bal és jobb oldal helyessége
     * 
     * @param cu A fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const{
        left->checkSemantics(cu);
        right->checkSemantics(cu);
    }

    /**
     * @brief Optimalizálja a bal és jobb oldalt, ha lehet
     */
    void optimize();

    /**
     * @brief Visszaadja, hogy a művelet helyettesíthető-e konstanssal
     * 
     * @return true Ha a művelet helyettesíthető-e konstanssal
     * @return false Egyébként
     */
    bool isConst() const {return left->isConst() && right->isConst();}

    void calculateColorTree(LinkingUnit& lu, unsigned int expectedOut);
};


#endif //binaryExpression_H
