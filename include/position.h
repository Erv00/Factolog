#ifndef position_H
#define position_H


class Position {
    public:
    float x,y;

    Position(float x, float y):x(x),y(y){}
    Position operator+(const Position& delta) const;
    bool operator<(const Position& p2) const;
    Position& operator+=(const Position& p2);
    Position operator/(float f) const;

    bool inBounds(int width, int height = -1);
    float distanceTo(const Position& p2) const;
};

#endif //position_H
