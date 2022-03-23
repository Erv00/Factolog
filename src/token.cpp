#include "token.h"

#include <memtrace.h>

Token::Token(std::string cont): content(cont){}
Token::Token(const char* cont): content(cont){}
Token::Token(char c){
    content = std::string(1, c);
}

/*Token::Token(const Token& t){
    content = t.content;
}*/

size_t Token::length() const {
    return content.length();
}

char& Token::operator[](int i){
    return content[i];
}

const char& Token::operator[](int i) const {
    return content[i];
}

bool Token::operator==(const Token& t) const{
    return content == t.content;
}

bool Token::operator==(const std::string& s) const{
    return content == s;
}

bool Token::operator==(const char* s) const{
    return content == s;
}

bool Token::operator==(const char c) const{
    return content.length() == 1 && content[0] == c;
}

bool Token::operator!=(const Token& t) const{
    return !(*this == t);
}
bool Token::operator!=(const std::string& s) const{
    return !(*this == s);
}
bool Token::operator!=(const char* s) const{
    return !(*this == s);
}
bool Token::operator!=(const char c) const{
    return !(*this == c);
}

Token::operator std::string(){
    return content;
}

std::string& Token::getContent(){
    return content;
}
const std::string& Token::getContent() const{
    return content;
}

bool Token::isEOF() const {
    return content == "";
}

std::ostream& operator<<(std::ostream& os, const Token& t){
    os << t.getContent();
    return os;
}
