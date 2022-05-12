/**
 * @file assignment.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Értékadás
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef assignment_H
#define assignment_H

#include "asyncExpression.h"
#include "identifier.h"
#include "number.h"

#include "memtrace.h"

namespace factolog {

/**
 * @brief Értékadás
 */
class Assignment : public AsyncExpression {
    Identifier *to;         ///<Az értéket kapó változó
    ValueExpression *val;   ///<A kapott érték

    public:
    /**
     * @brief Assignment felszabadítása
     */
    ~Assignment(){delete to; delete val;};

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return Assignment* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static Assignment* parse(Lexer& lex);

    /**
     * @brief Visszaadja az értékadás célját
     * 
     * @return const Identifier* Az értékadás célja
     */
    Identifier* getIdentifier() const {return to;}

    /**
     * @brief Visszaadja az értékadás értékét
     * 
     * @return const ValueExpression* Az értékadás értéke
     */
    ValueExpression* getValue() const {return val;}

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;

    /**
     * @brief Semantikailag ellenőrzi az egyenlőségadást
     * 
     * Ellenőrzött tulajdonságok:
     * @li Baloldal létezik
     * @li Jobboldal helyes
     * @li Van-e már a baloldalhoz rendelve érték
     * 
     * @param cu Fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const;

    /**
     * @brief Optimalizálja az értékadást, ha lehet
     */
    void optimize(){
        if(val->isConst()){
            int v = val->calculate();
            delete val;
            val = new Number(v);
        }else
            val->optimize();
    }

    AsyncExpression* clone() const;

    /**
     * @brief Lecseréli a változók azonosítóját a modulokban a kapcsolatban lévőkkel
     * 
     * @param translation Régi-új változónév összerendelések
     */
    void translate(const Translator& translation);
    void calculateColorTree(LinkingUnit* lu);
};


} //namespace factolog

#endif //assignment_H
