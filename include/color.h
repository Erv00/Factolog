#ifndef color_H
#define color_H

#include <ostream>
#include <memtrace.h>

class Color {
    unsigned int color;
    public:
    Color(unsigned int col):color(col){};
    Color(std::string str);
    Color():color(0){};

    bool operator!=(unsigned int i) const;
    bool operator!=(const Color& c) const;
    bool operator==(const Color& c) const;
    Color operator++();
    Color operator++(int i);

    bool operator<(const Color& col) const;

    unsigned int toConst() const;

    operator std::string() const;

};

std::ostream& operator<<(std::ostream& os, const Color& col);

#endif //color_H
