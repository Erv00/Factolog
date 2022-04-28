/**
 * @file token.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Egy token leírása
 * @date 2022-03-24
 * @copyright Copyright (c) 2022
 */
#ifndef token_H
#define token_H

#include <string>
#include <memtrace.h>

namespace factolog {

/**
 * @brief Egy lexikai token
 */
class Token {
    private:
    std::string content;    ///<A token tartalma
    public:
    /**
     * @brief Új Token létrehozása
     * @param s A token tartalma
     */
    Token(std::string s);
    /**
     * @brief Új Token létrehozása
     * @param s A token tartalma
     */
    Token(const char* s);
    /**
     * @brief Új Token létrehozása
     * @param c A token tartalma
     */
    Token(char c);

    /**
     * @brief A token tartalmának mérete
     * 
     * @return size_t A token tartalmának mérete
     */
    size_t length() const;
    
    /**
     * @brief Visszadja a token tartalmának az i. karakterét
     * 
     * @param i i
     * @return char& Referencia az i. karakterre
     */
    char& operator[](int i);

    /**
     * @brief Visszadja a token tartalmának az i. karakterét
     * 
     * @param i i
     * @return char& Referencia az i. karakterre
     */
    const char& operator[](int i) const;

    /**
     * @brief Összehasonlít két tokent
     * 
     * @param t A másik token
     * @return true Ha egyenlők
     * @return false Egyébként
     */
    bool operator==(const Token& t) const;

    /**
     * @brief Összehasonlítja a tokent egy sztringgel
     * 
     * @param s A másik sztring
     * @return true Ha egyenlők
     * @return false Egyébként
     */
    bool operator==(const std::string&) const;

    /**
     * @brief Összehasonlítja a tokent egy c-sztringgel
     * 
     * @param s A másik c-sztring
     * @return true Ha egyenlők
     * @return false Egyébként
     */
    bool operator==(const char* s) const;

    /**
     * @brief Összehasonlítja a tokent egy karakterrel
     * 
     * @param c A megadott karakter
     * @return true Ha egyenlők
     * @return false Egyébként
     */
    bool operator==(const char c) const;

    /**
     * @brief Összehasonlítja a két tokent
     * 
     * @param t A másik token
     * @return true Ha nem egyenlők
     * @return false Egyébként
     */
    bool operator!=(const Token& t) const;
    //bool operator!=(const std::string& s) const;
    /**
     * @brief Összehasonlítja a tokent egy c-sztringgel
     * 
     * @param s a c-sztring
     * @return true Ha nem egyenlők
     * @return false Egyébként
     */
    bool operator!=(const char* s) const;
    //bool operator!=(const char c) const;

    /**
     * @brief Sztrigre castol
     * 
     * @return std::string A token tartalma sztringként
     */
    operator std::string();

    /**
     * @brief Visszaadja a token tartalmát
     * 
     * @return std::string& a token tartalma
     */
    std::string& getContent();

    /**
     * @brief Visszaadja a token tartalmát
     * 
     * @return const std::string& A token tartalma
     */
    const std::string& getContent() const;

    /**
     * @brief Visszadja, hogy van-e még token
     * 
     * @return true Ha van még token
     * @return false Ha már nincs több token
     */
    bool isEOF() const;
};

/**
 * @brief Kiír egy tokent a megadott stream-re
 * 
 * @param os A megadott stream
 * @param t A kiírandó token
 * 
 * @return std::ostream& A megadott stream
 */
std::ostream& operator<<(std::ostream& os, const Token& t);

} //namespace factolog

#endif //token_H
