/**
 * @file position.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Pozíció
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef position_H
#define position_H

#include "memtrace.h"

namespace factolog {

/**
 * @brief Pozíció
 */
class Position {
    public:
    float x;    ///< X koordináta
    float y;    ///< Y koordináta

    /**
     * @brief Új Position létrehozása
     * 
     * @param x X koordináta
     * @param y Y koordináta
     */
    Position(float x, float y):x(x),y(y){}

    /**
     * @brief Összeadás
     * 
     * 2 vektor összeadása
     * 
     * @param delta Az eltolás
     * @return Position Az új pozíció
     */
    Position operator+(const Position& delta) const;
    
    /**
     * @brief Két pozíció összehasonlítása
     * 
     * Matematikailag nincs értelme, std::set-hez kell
     * 
     * @param p2 A másik pozíció
     * @return true Ha x0 < x1 || (x0=x1 && y0 < y2)
     * @return false Egyébként
     */
    bool operator<(const Position& p2) const;

    /**
     * @brief Eltolás
     * 
     * @param p2 Eltolás
     * @return Position& Az eltolt pozíció
     */
    Position& operator+=(const Position& p2);

    /**
     * @brief Osztás
     * 
     * Az osztás a matematikai értelmében történik.
     * 
     * @param f Az osztó
     * @return Position Az eredmény
     */
    Position operator/(float f) const;

    /**
     * @brief Ellenőrzi, hogy a pozíció a megadott téglalapon belül van-e
     * 
     * A téglalapon az első síknegyedben helyezkedik el, és az egyik sarka az origó
     * 
     * @param width A téglalap szélessége
     * @param height A téglalap magassága, vagy -1 ha egyenlő a szélességgel
     * @return true Ha a pozíció a téglalapon belül van
     * @return false Egyébként
     */
    bool inBounds(int width, int height = -1);

    /**
     * @brief Megadja a távolságot a másik pozícióig
     * 
     * @param p2 A másik pozíció
     * @return float A távolság
     */
    float distanceTo(const Position& p2) const;
};

} //namespace factolog

#endif //position_H
