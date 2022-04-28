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
#include <map>
#include <memtrace.h>

namespace factolog {

class Identifier;
class Translator;
class LinkingUnit;

/**
 * @brief Bal oldal
 */
#define LEFT 0

/**
 * @brief Jobb oldal
 */
#define RIGHT 1

/**
 * @brief Base class az értéket hordozó osztályoknak 
 */
class ValueExpression : public TreeNode {
    protected:
    Color outColor;      ///<A kombinátor kimeneti színe
    Color inColors[2];   ///<A kombinátor bemenetei
    
    public:
    /**
     * @brief Új ValueExpression létrehozása
     */
    ValueExpression(): outColor(0){
        inColors[0] = 0;
        inColors[1] = 0;
    }

    /**
     * @brief Value Expression felszabadítása
     */
    virtual ~ValueExpression(){};

    /**
     * @brief Másolat létrehozása
     * 
     * A leszármaztatott másoló konstruktorát hívja
     * 
     * @return AsyncExpression* A dinamikusan foglalt másolat címe
     */
    virtual ValueExpression* clone() const = 0;

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

    /**
     * @brief Visszadja a kombinátor kimeneti színét
     * 
     * Az alap implementáció a kombinátor színét adja vissza, ami alapesetben mindig 0.
     * Identifier esetében az előre megadott színt adja vissza.
     * 
     * @param lu A linkelési egység
     * @return Color A kombinátor kimeneti színe
     */
    virtual Color getOutColor(LinkingUnit* lu) const{
        (void)lu;
        return outColor;
    }

    /**
     * @brief Megadja, hogy a kombinátornak van-e színe.
     * 
     * Az alap implementáció a kombinátor színét adja vissza, ami alapesetben mindig 0,
     * ezért mindig false a viszzatérési érték.
     * Identifier esetében az előre megadott a szín, mindig igazzal tér vissza.
     * 
     * @param lu A linkelési egység
     * @return true Ha van színe
     * @return false Egyébként
     */
    virtual bool hasOutColor(LinkingUnit* lu) const {return getOutColor(lu).isValid();}

    /**
     * @brief Beállítja a kimeneti színt
     * 
     * @param col 
     */
    void setOutColor(Color col){outColor = col;}

    /**
     * @brief Visszaadja a kombinátor bemenetének a színét
     * 
     * @param index A bemenet indexe
     * @return Color A bemenet színe
     */
    Color getInColor(size_t index=0) const;

    /**
     * @brief Megadja, hogy a kombinátornak a megadott bemenetének van-e színe
     * 
     * @param index A bemenet indexe
     * @return true Ha a bemenetnek van színe
     * @return false Egyébként
     */
    bool hasInColor(size_t index=0) const;

    /**
     * @brief Bállítja a bemenet színét
     * 
     * @param col A szín
     * @param index Bemenet indexe, 0 a bal 1 a jobb
     */
    void setInColor(Color col, size_t index=0);

    /**
     * @brief Elkészíti a szín-fát
     * 
     * Minen kombinátornak meghatározza a bemeneti és kimeneti színeit
     * 
     * @param lu Linkelési egység
     * @param expectedOut A kombinátor kimeneti színe
     */
    virtual void calculateColorTree(LinkingUnit* lu, Color expectedOut) = 0;

    /**
     * @brief Lecseréli a változók azonosítóját a modulokban a kapcsolatban lévőkkel
     * 
     * @param translation Régi-új változónév összerendelések
     */
    virtual void translate(const Translator& translation) = 0;
}; 

} //namespace factolog

#endif //valueExpression_H
