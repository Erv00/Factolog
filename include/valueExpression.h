/**
 * @file valueExpression.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Értéket hordozó osztály
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef valueExpression_H
#define valueExpression_H

#include "treenode.h"

/**
 * @brief Base class az értéket hordozó osztályoknak 
 */
class ValueExpression : public TreeNode {
    public:
    /**
     * @brief Value Expression felszabadítása
     */
    virtual ~ValueExpression(){};

    /**
     * @brief Optimalizálja a kifejezést, ha lehet
     */
    virtual void optimize() = 0;
    /**
     * @brief Visszaadja, hogy a művelet helyettesíthető-e konstanssal
     * 
     * @return true Ha a művelet helyettesíthető-e konstanssal
     * @return false Egyébként
     */
    virtual bool isConst() const = 0;

    /**
     * @brief Kiszámítja a művelet értékét, ha konstans
     * 
     * @throws const char* Ha a kifejezés nem konstans. Normál futásnál nem fordul elő
     * 
     * @return int A kifejezés értéke
     */
    virtual int calculate() const = 0;
}; 

#endif //valueExpression_H
