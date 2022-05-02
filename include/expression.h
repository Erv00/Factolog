/**
 * @file expression.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Egyes precedenciaszintű műveletek
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef expression_H
#define expression_H


#include "binaryExpression.h"
#include <ostream>
#include "memtrace.h"

namespace factolog {

class Lexer;

/**
 * @brief Egyes precendenciaszintű művelet 
 * @sa Precedence
 */
class Expression : public BinaryExpression {
    public:
    /**
     * @brief Egyes precedenciaszintű műveletek
     * @sa Precedence
     */

    /**
     * @brief Új Expression létrehozása
     */
    Expression(){}

    public:
    /**
     * @brief Új Expression létrehozása
     * 
     * @param e A másolandó kifejezés
     */
    Expression(const Expression& e);

    ValueExpression* clone() const;

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return ValueExpression* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static ValueExpression* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;

    int calculate() const;
};


} //namespace factolog

#endif //expression_H
