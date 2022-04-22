/**
 * @file value.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Érték (konstans vagy azonosító)
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef value_H
#define value_H

#include "valueExpression.h"
#include "lexer.h"
#include <memtrace.h>

/**
 * @brief Érték
 */
class Value : public ValueExpression {
    public:
    /**
     * @brief Value felszabadítása
     */
    virtual ~Value(){};

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return Value* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static Value* parse(Lexer& lex);
};


#endif //value_H
