/**
 * @file dot.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Kiírás dot formátumban
 * @version 0.1
 * @date 2022-03-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef lexemes_H
#define lexemes_H

#include <ostream>
#include <memtrace.h>

namespace factolog {

/**
 * @brief Dot formátumba kiírós függvényeket tartalmazó osztály
 * 
 */
class Dot {
    public:
    /**
     * @brief Kapcsolat hoz létre a két objektum között
     * 
     * @param os Kimeneti stream
     * @param from Kapcsolat kiindulása
     * @param to Kapcsolat végpontja
     * @param label A kapcsolat felirata
     * @return std::ostream& Kimeneti stream
     */
    static std::ostream& dotConnection(std::ostream& os, const void *from, const void *to, const char *label="");

    /**
     * @brief Csomópont létrehozása megadott paraméterekkel
     * 
     * @param os Kimeneti stream
     * @param obj Objektum
     * @param label Csomópont címkéje
     * @param style Csomópont stílusa
     * @return std::ostream& Kimeneti stream
     */
    static std::ostream& dotNode(std::ostream& os, const void *obj, const char *label, const char *style);
};

} //namespace factolog

#endif //lexemes_H
