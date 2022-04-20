#ifndef connection_H
#define connection_H

typedef unsigned int EID;

class Connection {
    public:
    EID from;
    EID to;
    bool isRed;

    Connection(EID fr, EID to, bool red): from(fr), to(to), isRed(red){}
};

#endif //connection_H
