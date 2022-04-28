/**
 * @file color.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Egy kapcsolat színének leírása
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef color_H
#define color_H

#include <string>
#include <ostream>
#include <memtrace.h>

namespace factolog {

/**
 * @brief Egy kapcsolat színének leírása
 * 
 * @note Factorio-ban a jeleknek van típusa, azonban ezek csak a nevükben térnek el, így nincs szükség leszármaztatásra
 * 
 */
class Color {
    std::string signal;         ///< A szín neve
    std::string signalType;     ///< A szín típusa
    unsigned int constantValue; ///< Konstans esetén az értéke
    
    /**
     * @brief Meghatározza, hogy a színt lehet-e konstansként értelmezni
     * 
     * @return true Ha a szín értelmezhető konstansként
     * @return false Egyébként
     */
    bool isNumeric() const;
    
    public:
    /**
     * @brief Új Color létrehozása
     * 
     * @param col A szín sorszáma ha a szín a virtual típusba tartozik, vagy a konstans értéke
     */
    Color(unsigned int col);
    
    /**
     * @brief Új Color létrehozása
     * 
     * @param str A szín típusa és neve [\<típus\>:]\<név\> formátumban. Ha nincs megadva típus, a virtual az alapértelmezett 
     */
    Color(std::string str);

    /**
     * @brief Új Color létrehozása
     */
    Color():signal("signal-A"), signalType("virtual"), constantValue(0){};

    /**
     * @brief Szín összehasonlítása konstansal
     * 
     * @param i A konstans
     * @return true Ha a színek megegyeznek
     * @return false Egyébként
     */
    bool operator!=(unsigned int i) const;
    
    /**
     * @brief Szín összehasonlítása másik színnel
     * 
     * @param c A másik szín
     * @return true Ha a színek egyeznek
     * @return false Egyébként
     */
    bool operator!=(const Color& c) const;
    
    /**
     * @brief Szín összehasonlítása konstansal
     * 
     * @param i A konstans
     * @return true Ha a színek megegyeznek
     * @return false Egyébként
     */
    bool operator==(unsigned int i) const;
    
    /**
     * @brief Szín összehasonlítása másik színnel
     * 
     * @param c A másik szín
     * @return true Ha a színek egyeznek
     * @return false Egyébként
     */
    bool operator==(const Color& c) const;

    /**
     * @brief Szín konstans értékének inkrementálása
     * 
     * @return Color Az inkrementált szín
     */
    Color operator++();

    /**
     * @brief Szín konstans értékének poszt inkrementálása
     * 
     * @return Color Az inkrementált szín
     */
    Color operator++(int);

    /**
     * @brief Szín összehasonlítása másik színnel
     * 
     * @note Nem a matematikai értelemben vannak összehasonlítva, csak az STL függvények miatt kell
     * 
     * @param col A másik szín
     * @return true Ha a másik szín nem kisebb
     * @return false Egyébként
     */
    bool operator<(const Color& col) const;

    /**
     * @brief Visszadja konstansként az értéket
     * 
     * @warning Nem konstans értékű jelre definiálatlan az eredmény
     * 
     * @return unsigned int A konstans értéke
     */
    unsigned int toConst() const;
    
    /**
     * @brief Visszaadja a szín Factorio-beli típusát
     * 
     * @note @sa Color
     * 
     * @return std::string 
     */
    std::string getType() const{return signalType;}

    /**
     * @brief Visszaadja a jelet mint sztring
     * 
     * A visszadot sztring formátuma: \<típus>-\<név>
     * 
     * @return std::string A szín sztring formátumban
     */
    operator std::string() const;

    /**
     * @brief Megadja, hogy az adott szín érvényes-e
     * 
     * @return true Ha a szín érvényes
     * @return false Egyébként
     */
    bool isValid() const;

};

/**
 * @brief Color kiírása stream-be
 * 
 * @param os A kimeneti stream
 * @param col A kiírandó szín
 * @return std::ostream& A kimeneti stream
 */
std::ostream& operator<<(std::ostream& os, const Color& col);

} //namespace factolog

#endif //color_H
