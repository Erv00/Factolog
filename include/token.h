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
    
    char& operator[](int i);
    const char& operator[](int i) const;

    bool operator==(const Token&) const;
    bool operator==(const std::string&) const;
    bool operator==(const char*) const;
    bool operator==(const char) const;

    bool operator!=(const Token&) const;
    bool operator!=(const std::string&) const;
    bool operator!=(const char*) const;
    bool operator!=(const char) const;

    operator std::string();

    std::string& getContent();
    const std::string& getContent() const;

    bool isEOF() const;
};

std::ostream& operator<<(std::ostream&, const Token&);

#endif //token_H
