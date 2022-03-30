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
    enum BinaryOperator {
        PLUS, MINUS, AND, OR, XOR
    };

    private:
    enum BinaryOperator op; ///<Végzendő művelet

    public:
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


#endif //expression_H
