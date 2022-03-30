/**
 * @file identifier.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Azonosító
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef identifier_H
#define identifier_H

#include "value.h"
#include <string>

/**
 * @brief Azonosító
 */
class Identifier : public Value{
    std::string name;   ///<Az azonosító neve

    /**
     * @brief Új Identifier létrehozása
     * @param name Az azonosító neve 
     */
    Identifier(std::string name):name(name){};

    public:
    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return Identifier* A tokenekből előállított @ref AST
     * @sa @ref AST 
     * @throws UnexpectedSymbolError Ha a következő Token nem érvényes azonosító
     */
    static Identifier* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;

    /**
     * @brief Az azonosító neve
     * 
     * @return std::string& Az azonosító neve
     */
    const std::string& getName()const {return name;};

    /**
     * @brief Összehasonlít két azonosítót
     * 
     * @param b A másik azonosító
     * @return true Ha betűrendben b később van
     * @return false Egyébként
     */
    bool operator<(const Identifier& b) const{
        return name < b.name;
    }

    /**
     * @brief Szemantika ellenőrzést végez
     * 
     * Ellenőrzött tulajdonságok:
     * @li A változó létezése
     * @li A változónak már van értéke (Erre csak figyelmeztetés van)
     * 
     * @param cu A fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const;

    void optimize(){}
    bool isConst() const {return false;/*Could be better*/}
    int calculate() const {throw "Identifier is not const";}
};


#endif //identifier_H