/**
 * @file arithmeticCombinator.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Aritmetikai kombinátor
 * @version 0.1
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022
 * Műveletvégrehajtó egység, bináris műveleteket tud végezni.
 */
#ifndef arithmeticCombinator_H
#define arithmeticCombinator_H

#include "combinator.h"

/**
 * @brief Aritmetikai kombinátor
 * 
 * Két operandussal végez műveletet
 * 
 */
class ArithmeticCombinator : public Combinator {
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
};

#endif //arithmeticCombinator_H
