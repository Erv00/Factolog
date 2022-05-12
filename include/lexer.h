/**
 * @file lexer.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Factolog lexikai feldolgozása
 * @version 0.1
 * @date 2022-03-08
 * @copyright Copyright (c) 2022
 */
#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "token.h"
#include <memtrace.h>

/**
 * @brief Lexikai értelmező
 */
class Lexer {
    std::istream& is;                           ///<Az input stream
    std::vector<Token> tokens;                  ///<A stream összes tokenje
    std::vector<Token>::iterator currentToken;  ///<A jelenlegi tokenre mutató iterator
    std::vector<Token>::iterator nextToken;     ///<A következő tokenre mutató iterator
    static Token END_TOKEN;                     ///<A streamot lezáró token

    /**
     * @brief Eldönti egy addot karakterről, hogy Single Character Token (SCT)-e
     * 
     * Egy karakter akkor SCT, ha nem DCT, és önmagában lexáma.
     * Ezek jelenleg a strukturális elemek, és a műveletek a DCTk kivételével.
     * 
     * @param c A vizsgált karakter
     * @return true Ha a karekter SCT
     * @return false Egyébként
     */
    bool isSingleCharToken(char c) const;

    /**
     * @brief Eldönti a stringben következő 2 karakterről, hogy Double Character Token (DCT)-e 
     *
     * A következő 2 karakter akkor DCT, ha együtt egy lexémát alkotnak.
     * Ez jelenleg csak a <<, a >>, és a ** lexémák
     * 
     * @param it A következő karakterre mutató string iterátor
     * @return true Ha a karakterek DCTk
     * @return false Egyébként
     */
    bool isTwoCharToken(std::string::iterator& it) const;

    /**
     * @brief Sor feldolgozása
     * @param line A feldolgozandó sor
     */
    void lexLine(std::string line);

public:
    /**
     * @brief Új Lexer létrehozása
     * @param _is Bemeneti stream
     */
    Lexer(std::istream& _is);
    /**
     * @brief Új Lexer létrehozása
     * @param _is Bemeneti stream
     */
    Lexer(std::ifstream& _is);

    /**
     * @brief Konstans referencia a tokenekre
     * @return const std::vector<Token>& konstans referencia a tokenekre
     */
    const std::vector<Token>& getTokens() const {return tokens;};

    /**
     * @brief Tokenizálást végez a megadott stream-en
     * 
     * A tokenizálás lépései:
     * @li Behúzás törlése
     * @li Kommentek törlése
     * @li Új-sorok törlése
     * @li Tokenekre bontás
     */
    void operator()();

    /**
     * @brief Visszadja következő tokent, de nem fogyasztja el
     * 
     * Ha a nincs következő token akkor az END_TOKENT adja vissza 
     * @return Token& A következő token
     */
    Token& next() const;

    /**
     * @brief Ellenőrzi, hogy a következő token a megadott token-e, és elfogyasztja
     * 
     * Ha nem a megadott tokent találja, parser hibát dob
     * 
     * @param t Elvárt token
     */
    void except(Token t);

    /**
     * @brief Elfogyasztja a következő tokent
     * 
     * Biztonságosan meghívható ha nincs következő token
     * 
     */
    void consume();

    /**
     * @brief Visszadja a jelenlegi tokent
     * 
     * @return Token& A jelenlegi token
     */
    Token& current() const;

    /**
     * @brief Visszaadja, hogy a következő token END_TOKEN-e
     * 
     * Egyenlő a this->current().isEOF() értékével
     * 
     * @return true Ha elérte a token-sorozat végét
     * @return false Egyébként
     */
    bool eof() const;
};

/**
 * @brief Lexer tokenlistájának kiírása
 * Csak tesztelési szempontból van, használata felesleges
 * @param os A kimeneti stream
 * @param l A lexer
 * @return std::ostream& A kimeneti stream
 */
std::ostream& operator<<(std::ostream& os, const Lexer& l);
#endif
