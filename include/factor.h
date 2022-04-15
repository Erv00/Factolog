/**
 * @file factor.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Hármas precedenciaszintű műveletek
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef factor_H
#define factor_H

#include "binaryExpression.h"
#include "lexer.h"

/**
 * @brief Hármas precedenciaszintű művelet
 * 
 * Ezen a precedenciaszinten csak a hatványozás (**) áll
 * 
 * @sa Precedence
 */
class Factor : public BinaryExpression {
    /**
     * @brief Új Factor létrehozása
     */
    Factor(){}

    public:
    /**
     * @brief Új Factor létrehozása
     * 
     * @param f A másolandó Factor
     */
    Factor(const Factor& f):BinaryExpression(f){}


    ValueExpression* clone() const {return new Factor(*this);}

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


#endif //factor_H
