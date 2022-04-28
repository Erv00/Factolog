/**
 * @file exceptions.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Hibák leírása
 * @copyright Copyright (c) 2022
 */
#ifndef exceptions_H
#define exceptions_H

#include <exception>
#include <sstream>

#include "lexer.h"
#include "identifier.h"
#include <memtrace.h>

namespace factolog {

/**
 * @brief Base class feldolgozás közbeni hibáknak
 */
class ParserError : public std::exception{
    protected:
    char *whatData; ///< A hiba leírása
    public:
    /**
     * @brief Visszaadja a hiba leírását
     * @return const char* a hiba leírása 
     */
    const char* what() const throw();

    /**
     * @brief Felszabadítja a whatData mezőt
     */
    virtual ~ParserError() throw();
};

/**
 * @brief Várt token hiba
 * 
 * Más tokent vártunk
 */
class TokenExpectedError : public ParserError {
    public:
    /**
     * @brief Új TokenExpectedError létrehozása
     * 
     * @param expected Az elvárt token
     * @param got Az érkezett token
     */
    TokenExpectedError(Token expected, Token got);
    /**
     * @brief TokenExpectedError felszabadítása
     */
    ~TokenExpectedError() throw() {};
};

/**
 * @brief Váratlan token hiba
 * 
 * Váratlan tokent talált a bemeneten, ez lehet EOF is
 */
class UnexpectedSymbolError : public ParserError {
    public:
    /**
     * @brief Új UnexpectedSymbolError létrehozása
     * 
     * @param got A váratlan token
     */
    UnexpectedSymbolError(Token got);
    /**
     * @brief UnexpectedSymbolError felszabadítása
     */
    ~UnexpectedSymbolError() throw() {};
};

/**
 * @brief Túlcsordulási hiba
 * 
 * A konstansoknak a [0,2147483647[ intervallumba kell esniük
 */
class UnableToRepresentError : ParserError {};

/**
 * @brief Base class programozói hibáknak
 */
class ProgrammingError : public std::exception {
    protected:
    char *whatData; ///<A hiba leírása
    public:
    /**
     * @brief ProgrammingError felszabadítása
     */
    virtual ~ProgrammingError() throw();
    /**
     * @brief Visszaadja a hiba leírását
     * @return const char* a hiba leírása 
     */
    const char* what() const throw();
};

/**
 * @brief Paraméter nélkül modul
 * 
 * A praméter nélküli modulok nem tudnak kapcsolatba lépni a külvilággal
 */
class EmptyParameterListError : public ProgrammingError{
    public:
    /**
     * @brief Új EmptyParameterListError létrehozása
     * @param t Token ahol a hiba történt
     */
    EmptyParameterListError(Token t);
    /**
     * @brief EmptyParameterListError felszabadítása
     */
    ~EmptyParameterListError() throw(){};
};

/**
 * @brief A modul már definiálva van
 */
class ModuleAlreadyDefinedError : public ProgrammingError {
    public:
    /**
     * @brief Új ModuleAlreadyDefinedError létrehozása
     * 
     * @param identifier A modul azonosítója
     */
    ModuleAlreadyDefinedError(Token identifier);
};

/**
 * @brief Definiálatlan változó
 */
class UndefinedVariableError : public ProgrammingError{
    public:
    /**
     * @brief Új UndefinedVariableError létrehozása
     * 
     * @param var A definiálatlan változó 
     */
    UndefinedVariableError(const Identifier* var);
};

/**
 * @brief Újraértékadás
 */
class VariableReassignmentError : public ProgrammingError{
    public:
    /**
     * @brief Új VariableReassignmentError létrehozása
     * 
     * @param to Az újradefiniált változó
     */
    VariableReassignmentError(const Identifier* to);
};

/**
 * @brief Definiálatlan modul
 */
class ModuleNotDefinedError : public ProgrammingError{
    public:
    /**
     * @brief Új ModuleNotDefinedError létrehozása
     * 
     * @param module A definiálatlan modul 
     */
    ModuleNotDefinedError(const Identifier* module);
};

/**
 * @brief Eltérő paraméterszám
 */
class MismatchedParametersError : public ProgrammingError{
    public:
    /**
     * @brief Új MismatchedParametersError létrehozása
     * 
     * @param at A hiba helye
     */
    MismatchedParametersError(const Identifier* at);
};

/**
 * @brief Már definiált változó
 */
class VariableAlreadyDefinedError : public ProgrammingError{
    public:
    /**
     * @brief Új VariableAlreadyDefinedError létrehozása
     * 
     * @param var A változó azonosítója
     */
    VariableAlreadyDefinedError(const Identifier* var);
};
} //namespace factolog

#endif //exceptions_H
