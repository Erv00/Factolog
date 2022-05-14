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
#include "argumentParser.h"
#include "compilationUnit.h"

#include "memtrace.h"

namespace factolog {

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

    std::map<const Identifier, Module*> definedModules;             ///<Definiált modulok
    std::map<const Identifier, CompilationUnit*> compilationUnits;  ///<A modulok fordítási egységei

    bool doPrintBlueprint;  ///<Kell tervrajz kimenet?
    bool doPrintDot;        ///<Kell dot kimenet?
    std::vector<std::string> userColorMapping;  ///<A felhasználó által megadott szín-jel összerendelések

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
     * @brief Új Compiler létrehozása konfigurációval
     * 
     * @param config A konfiguráció
     */
    Compiler(const Configuration& config);

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

    /**
     * @brief Dot kimenet kiíratási szükség
     * 
     * @return true Ha a dot kimenet ki lesz írva
     * @return false Egyébként
     */
    bool& printDotFlag() { return doPrintDot; }
    
    /**
     * @brief Dot kimenet kiíratási szükség
     * 
     * @return true Ha a dot kimenet ki lesz írva
     * @return false Egyébként
     */
    const bool& printDotFlag() const { return doPrintDot; }

    /**
     * @brief Blueprint kimenet kiíratási szükség
     * 
     * @return true Ha a tervrajz kimenet ki lesz írva
     * @return false Egyébként
     */
    bool& printBlueprintFlag() { return doPrintBlueprint; }

    /**
     * @brief Blueprint kimenet kiíratási szükség
     * 
     * @return true Ha a tervrajz kimenet ki lesz írva
     * @return false Egyébként
     */
    const bool& printBlueprintFlag() const { return doPrintBlueprint; }

};

} //namespace factolog

#endif //compiler_H
