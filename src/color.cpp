#include "color.h"
#include <sstream>

Color::Color(std::string str):constantValue(0){
    size_t sepPos = str.find(':');
    if(sepPos == str.npos)
        //No : found, assume virtual
        signalType = "virtual";
    else{
        //Found :, get type
        signalType = str.substr(0,sepPos);
        str = str.substr(sepPos+1);
    }
    if(str.substr(0,8) == "signal-") throw "This signal cannot be assigned";
    signal = str;
}

Color::Color(unsigned int col){
    constantValue = col;
    signalType = "virtual";
    signal = "signal-";
    signal += (char)('A'+col-1);
}

bool Color::isNumeric() const {
    return signal.substr(0,8) != "signal-";
}

bool Color::operator==(unsigned int i) const {
    return isNumeric() && (signal[signal.size()-1]-(unsigned int)'A' == i);
}

bool Color::operator==(const Color& col) const {
    if((isNumeric() ^ col.isNumeric()) != 0) return false;
    if(!isNumeric()) return signalType == col.signalType && signal == col.signal;
    else return constantValue == col.constantValue;
}

bool Color::operator!=(unsigned int i) const {
    return !(*this == i);
}

bool Color::operator!=(const Color& col) const {
    return !(*this == col);
}


Color Color::operator++(){
    constantValue++;
    signal[signal.size()-1]++;
    return *this;
}

Color Color::operator++(int){
    Color tmp = *this;
    ++*this;
    return tmp;
}

bool Color::operator<(const Color& col) const {
    return signal < col.signal;
}

Color::operator std::string() const {
    return signal;
}

unsigned int Color::toConst() const {
    return constantValue;
}

bool Color::isValid() const {
    return signal.length() > 0 && (signalType != "virtual" || signal.at(signal.length()-1) != '@');
}

std::ostream& operator<<(std::ostream& os, const Color& col){
    return os << (std::string)col;
}
