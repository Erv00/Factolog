#ifndef token_H
#define token_H

#include <string>

class Token {
    private:
    std::string content;
    public:
    Token(std::string);
    Token(const char*);
    Token(char);

    /*Token(const Token&);
    ~Token();
    Token& operator=(const Token&);*/

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
