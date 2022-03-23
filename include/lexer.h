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

class Lexer {
    std::vector<Token> tokens;
    std::istream& is;
    std::vector<Token>::iterator currentToken;   ///<A jelenlegi tokenre mutató iterator
    std::vector<Token>::iterator nextToken;      ///<A következő tokenre mutató iterator

    bool isSingleCharToken(char c) const;
    bool isTwoCharToken(std::string::iterator& it) const;


public:
    Lexer(std::istream& _is);
    Lexer(std::ifstream& _is);

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

    void lexLine(std::string line);

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
     */
    void except(Token);

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

std::ostream& operator<<(std::ostream& os, const Lexer& l);
#endif
