/**
 * @file compiler.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Egy fordítási folyamat leírása
 * @version 0.1
 * @date 2022-03-24
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef compiler_H
#define compiler_H

#include <istream>
#include <ostream>
#include <fstream>
#include <string>
#include <map>

#include "lexer.h"
#include "identifier.h"
#include "modules.h"
#include "compilationUnit.h"

#include <memtrace.h>

/**
 * @brief Egy fordítási folyamat reprezentálása
 * 
 * A fordítási folyamat lépései:
 * @li Forrás lexikai feldolgozása
 * @li @ref AST felépítése
 * @li Szemantikai ellenőrzés
 * @li Optimalizálás
 * @li Hardverterv előállítása
 */
class Compiler {
    std::istream *is;       ///<Bemeneti stream
    std::ostream *os;       ///<Kimeneti stream

    std::ifstream *ifs;     ///<Bemeneti fájlstream, NULL ha nem a compiler kezeli
    std::ofstream *ofs;     ///<Kimeneti fájlstream, NULL ha nem a compiler kezeli

    Lexer *lexer;           ///<Lexikai feldolgozó

    std::map<const Identifier, Module*> definedModules; ///<Definiált modulok

    /**
     * @brief Elvégzi a forrás lexikai feldolgozását 
     */
    void lex();

    /**
     * @brief Felépíti az @ref AST -t
     */
    void parse();

    /**
     * @brief Szemantikailag ellenőrzi a programot 
     */
    void check();

    /**
     * @brief Optimalizálja az @ref AST -t
     */
    void optimize();

    /**
     * @brief Átalakítja az @ref AST -t egy blueprint sztringgé
     */
    void compileBlueprint();

    /**
     * @brief Base64 enkódolja a blueprint sztringet
     */
    void encode();

    public:
    /**
     * @brief Új Compiler létrehozása
     * 
     * @param _is Forrás stream
     * @param _os Kimeneti stream
     */
    Compiler(std::istream& _is, std::ostream& _os);

    /**
     * @brief Új Compiler létrehozása
     * 
     * @param filename Forrásfájl
     * @param _os Kimeneti stream
     */
    Compiler(const char* filename, std::ostream& _os);

    /**
     * @brief Új Compiler létrehozása
     * 
     * @param inFilename Forrásfájl
     * @param outFilename Kimeneti fájl
     */
    Compiler(const char* inFilename, const char* outFilename);

    /**
     * @brief Compiler felszabadítása
     */
    ~Compiler();

    /**
     * @brief Értékadás
     * 
     * @param c A másolandó Compiler
     * @return Compiler& Az új Compiler
     */
    Compiler& operator=(const Compiler& c);

    /**
     * @brief Elvégzi a fordítás lépéseit
     * @sa Compiler
     * 
     */
    void compile();

};

#endif //compiler_H
