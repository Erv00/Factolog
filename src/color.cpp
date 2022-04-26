#include "color.h"

Color::Color(std::string str){
    if(str.substr(0,8) == "signal-") throw "This signal cannot be assigned";
    color = -1;
}

bool Color::operator!=(unsigned int i) const {
    return color != i;
}

bool Color::operator!=(const Color& col) const {
    return color != col.color;
}

bool Color::operator==(const Color& col) const {
    return color == col.color;
}

Color Color::operator++(){
    color++;
    return *this;
}

Color Color::operator++(int){
    Color tmp = *this;
    ++*this;
    return tmp;
}

bool Color::operator<(const Color& col) const {
    return color < col.color;
}

Color::operator std::string() const {
    return std::string("signal-")+(char)(('A'+color)-1);
}

unsigned int Color::toConst() const {
    return color;
}

std::ostream& operator<<(std::ostream& os, const Color& col){
    return os << (std::string)col;
}
