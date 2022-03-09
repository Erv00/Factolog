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

using std::vector;
using std::string;
using std::istream;

/**
 * @brief Egy lexikai token
 */
class Token {
private:
    const char *token;  ///<A token szöveges megjelenése
public:
    /**
     * @brief Új Token létrehozása
     * 
     * A megadott karaktertömb másolásra kerül
     * 
     * @param _token A token szöveges megjelenése
     */
    Token(const char *_token);
    /**
     * @brief Új Token létrehozása
     * @sa Token::Token(const char*)
     * @param t 
     */
    Token(const Token& t);

    Token operator=(const Token& t);

    bool operator==(const Token& t) const;
    bool operator==(const char *c) const;

    static bool isValidToken(std::string tok);
    static bool isSingleCharToken(const char c);
};

class Lexer {
    vector<string> tokens;
    istream& is;

public:
    Lexer(istream& _is);
    Lexer(std::ifstream& _is);

    const vector<string>& getTokens() const {return tokens;};

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
};

std::ostream& operator<<(std::ostream& os, const Lexer& l);
#endif