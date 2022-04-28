/**
 * @file number.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Konstans számérték
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef number_H
#define number_H

#include "value.h"
#include <memtrace.h>

class LinkingUnit;

/**
 * @brief Konstans számérték
 */
class Number : public Value {
    int value;  ///<Szémkonstans

    public:
    /**
     * @brief Új Number létrehozása
     * @param val A számkonstans
     */
    Number(int val):value(val){};

    ValueExpression* clone() const {return new Number(value);}

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return Number* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */

    static Number* parse(Lexer& lex);
    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;

    void optimize(){}
    bool isConst() const {return true;}
    int calculate() const {return value;}

    void calculateColorTree(LinkingUnit* lu, Color expected) {(void)lu;setOutColor(expected);}
    void translate(const Translator& translation){(void)translation;}
};


#endif //number_H
