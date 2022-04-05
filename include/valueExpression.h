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
#include <vector>

/**
 * @brief Base class az értéket hordozó osztályoknak 
 */
class ValueExpression : public TreeNode {
    unsigned int outColor;
    std::vector<unsigned int> inColors;
    public:
    ValueExpression(): outColor(0){}
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

    unsigned int getOutColor() const{return outColor;}
    bool hasOutColor() const {return getOutColor() != 0;}
    void setOutColor(unsigned int col){outColor = col;}

    unsigned int getInColor(size_t index=0) const;
    bool hasInColor(size_t index=0) const;

    /**
     * @brief Set the In Color object
     * 
     * @param col 
     * @param index Index, 0 a bal 1 a jobb
     */
    void setInColor(unsigned int col, size_t index=0);

    virtual void calculateColorTree(unsigned int expectedOut) = 0;

}; 

#endif //valueExpression_H
