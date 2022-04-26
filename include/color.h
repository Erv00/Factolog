#ifndef color_H
#define color_H

#include <string>
#include <ostream>
#include <memtrace.h>

class Color {
    std::string signal;
    std::string signalType;
    unsigned int constantValue;
    bool isNumeric() const;
    public:
    Color(unsigned int col);
    Color(std::string str);
    Color():signal("signal-A"), signalType("virtual"), constantValue(0){};

    bool operator!=(unsigned int i) const;
    bool operator!=(const Color& c) const;
    bool operator==(unsigned int i) const;
    bool operator==(const Color& c) const;
    Color operator++();
    Color operator++(int i);

    bool operator<(const Color& col) const;

    unsigned int toConst() const;
    std::string getType() const{return signalType;}

    operator std::string() const;

};

std::ostream& operator<<(std::ostream& os, const Color& col);

#endif //color_H
