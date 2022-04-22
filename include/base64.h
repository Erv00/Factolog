/**
 * @file base64.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Base64 enkódoló
 * @version 0.1
 * @date 2022-03-30
 * 
 * @sa RFC 4648 section 4
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef base64_H
#define base64_H

#include <cstring>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <memtrace.h>

/**
 * @brief Base64 enkódolást végez
 */
class Base64 {
    static const char ALPHABET[];   ///<A base64 ABC [RFC 4648 section 4](https://datatracker.ietf.org/doc/html/rfc4648#section-4) által meghatározva
    std::string buf;                ///<A kódolt sztring tárolása
    unsigned char bitsRemaining;    ///<Az előző emésztett char-ból maradó bitek száma
    char remaining;                 ///<Az előző emésztett char-ból maradó bitek

    /**
     * @brief Megemészt egy karaktert
     * 
     * Kódolja a karakter megfelelő bitjeit, a többit elmenti
     * 
     * @param c A megemésztendő karakter
     */
    void feedChar(char c);
    
    public:
    /**
     * @brief Új Base64 enkóder létrehozása
     */
    Base64(): bitsRemaining(0), remaining(0){}

    /**
     * @brief Megemészt tesztszőleges adatot
     * 
     * @param data A kódolandó adat
     * @param len Az adat hossza, vagy 0 ha egyenlő strlen(data)
     */
    void encode(const char* data, size_t len=0);

    /**
     * @brief Lezárja az adott kódolást, és szügség esetén paddol
     * 
     * A függvény szügség esetén egyenlőségjelet tesz a buffer végére.
     * A következő @ref encode hívás eredménye a buffer végére kerül.
     * Ha nem került a buffer végére egyenlőségjel a két üzenet csak a hosszukból különböztethető meg
     */
    void addPadding();

    /**
     * @brief Visszaadja a kódoló bufferét
     * 
     * @return std::string& A kódoló buffere
     */
    std::string& getBuf() {return buf;};
};

/**
 * @brief Paddol és kiírja a kódoló tartalmát
 * 
 * @param os A kimeneti stream
 * @param b64 A kódoló
 * @return std::ostream& A kimeneti stream 
 */
std::ostream& operator<<(std::ostream& os, Base64& b64);

#endif //base64_H
