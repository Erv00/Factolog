/**
 * @file combinator.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Factorio aritmetiaki kombinátor
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 * Ez a Factorio-ban létező aritmetikai kombinátort reprezentáló osztály
 * 
 */
#ifndef combinator_H
#define combinator_H

#include "entity.h"

#include <memtrace.h>


/**
 * @brief Aritmetikai kombinátor
 * 
 * Két operandussal végez műveletet
 * 
 */
class ArithmeticCombinator : public Entity {
    public:
    /**
     * @brief Lehetséges kétoperandusú műveletek
     */
    enum Operation {PLUS, MINUS, MUL, DIV, MOD, EXP, LSHIFT, RSHIFT, AND, OR, XOR};

    Operation op;   ///< Az elvégzendő művelet

    /**
     * @brief Új ArithmeticCombinator létrehozása
     */
    ArithmeticCombinator();

    /**
     * @brief Új ArithmeticCombinator létrehozása
     * 
     * Az elvégzendő unáris kifejezéseket is kétoperandusúként kell elvégeni
     * 
     * @param ve Elvégzendő művelet
     */
    ArithmeticCombinator(const ValueExpression& ve);

    /**
     * @brief Új ArithmeticCombinator létrehozása
     * 
     * @param op Az elvégzendő művelet
     */
    ArithmeticCombinator(Operation op);

    /**
     * @brief "control_bahavior" meghatározása
     * 
     * @return std::string "control_behavior" JSON formában
     */
    std::string getControlString() const;

    /**
     * @brief "operation_string" meghatározása
     * 
     * @return std::string "operation_string" JSON formában
     */
    std::string getOperationString() const;
    std::string toBlueprint() const;
};

#endif //combinator_H
