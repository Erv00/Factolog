/**
 * @file unaryExpression.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Unáris operátorok
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef unaryExpression_H
#define unaryExpression_H

#include "valueExpression.h"
#include "lexer.h"
#include "memtrace.h"

namespace factolog {

/**
 * @brief Unáris operátor
 */
class UnaryExpression : public ValueExpression {
    public:
    /**
     * @brief Unáris operátorok
     */
    enum Operator {PLUS, MINUS, NOT};
    enum Operator op;       ///<Elvégzendő művelet
    ValueExpression *expr;  ///<Kifejezés, amire alkalmazni kell az operátort

    /**
     * @brief Új UnaryExpression létrehozása
     */
    UnaryExpression(){op=PLUS;expr=NULL;};

    /**
     * @brief Új UnaryExpression létrehozása
     * 
     * @param u A másolandó unáris kifejezés
     */
    UnaryExpression(const UnaryExpression& u):op(u.op){expr = u.expr->clone();}
    
    ValueExpression* clone() const {return new UnaryExpression(*this);}

    /**
     * @brief UnaryExpression felszabadítása
     */
    ~UnaryExpression(){delete expr;};


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

    /**
     * @brief Szemantika ellenőrzést végez
     * 
     * Ellenőrzött tulajdonságok:
     * @li A kifejezés
     * 
     * @param cu A fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const;

    /**
     * @brief Optimalizálja a kifejezést, ha lehet
     */
    void optimize();
    bool isConst() const {return expr->isConst();}
    int calculate() const;

    void calculateColorTree(LinkingUnit* lu, Color expected);
    void translate(const Translator& translation);
    EID addToBlueprint(Blueprint& bp) const;
};


} //namespace factolog

#endif //unaryExpression_H
