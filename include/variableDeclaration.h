/**
 * @file variableDeclaration.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Változó(k) deklarálása
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef variableDeclaration_H
#define variableDeclaration_H

#include "asyncExpression.h"
#include "identifier.h"
#include <vector>
#include "memtrace.h"

namespace factolog {

/**
 * @brief Változó(k) deklarálása
 */
class VariableDeclaration : public AsyncExpression {
    std::vector<Identifier*> varsDeclared;  ///<Deklarált változók
    
    /**
     * @brief Új VariableDeclaration létrehozása
     */
    VariableDeclaration(){}
    
    /**
     * @brief Új VariableDeclaration létrehozása
     * 
     * @param vd A másolandó deklaráció
     */
    VariableDeclaration(const VariableDeclaration& vd);

    public:
    AsyncExpression* clone() const {return new VariableDeclaration(*this);}
    /**
     * @brief VariableDeclaration felszabadítása
     */
    ~VariableDeclaration(){
        for(size_t i=0; i<varsDeclared.size(); i++)
            delete varsDeclared[i];
    }

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return VariableDeclaration* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static VariableDeclaration* parse(Lexer& lex);

    /**
     * @brief Visszaadja a deklarált változókat
     * 
     * @return std::vector<Identifier*>& Deklarált változók azonosítói
     */
    std::vector<Identifier*>& getDeclaredVariables() {return varsDeclared;}

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
     * @li A változók nem létezése
     * 
     * @param cu A fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const;

    void translate(const Translator& translation);
};


} //namespace factolog

#endif //variableDeclaration_H
