#include "position.h"

#include <cmath>

using namespace factolog;

Position Position::operator+(const Position& delta) const {
    return Position(x+delta.x,y+delta.y);
}

bool Position::operator<(const Position& p2) const {
    return x<p2.x || (x==p2.x && y<p2.y);
}

Position& Position::operator+=(const Position& p2){
    x+=p2.x;
    y+=p2.y;
    return *this;
}

Position Position::operator/(float f) const {
    return Position(x/f,y/f);
}

bool Position::inBounds(int width, int height){
    if(height < 0) height = width;

    return 0<=x && x<width && 0<=y && y<height;
}

float Position::distanceTo(const Position& p2) const {
    return std::sqrt(std::pow(x-p2.x,2)+std::pow(y-p2.y,2));
}
