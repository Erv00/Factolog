/**
 * @file constantCombinator.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Konstans kombinátor
 * @version 0.1
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022
 * Konstansokat tud kitenni a buszra
 */
#ifndef constantCombinator_H
#define constantCombinator_H

#include "combinator.h"

/**
 * @brief Konstans kombinátor
 * A Factorioban lévo Constant Combinatornak megefelelő osztály.
 */
class ConstantCombinator : public Combinator {
    std::map<Color, unsigned int> signals;   ///< A kiadott jelek

    public:
    /**
     * @brief Új ConstantCombinator létrehozása
     * 
     * @param sig A kimeneti jel
     * @param val A kimeneti jel értéke
     */
    ConstantCombinator(Color sig, unsigned int val);

    std::string getConnectionString() const;
    std::string getControlString() const;
};

#endif //constantCombinator_H
