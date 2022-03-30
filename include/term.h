/**
 * @file term.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Kettes precedenciaszintű műveletek
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef term_H
#define term_H

#include "binaryExpression.h"
#include "lexer.h"

/**
 * @brief Kettes precedenciaszintű művelet
 * @sa Precedence
 */
class Term : public BinaryExpression {
    public:
    /**
     * @brief Kettes precedenciaszintű műveletek
     * @sa Precedence
     */
    enum BinaryOperator {
        MUL, DIV, MOD, LSHIFT, RSHIFT
    };

    private:
    enum BinaryOperator op; ///< Elvégzendő művelet

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


#endif //term_H
