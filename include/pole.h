#ifndef pole_H
#define pole_H

#include "entity.h"

class Pole : public Entity{
    public:
    Pole(std::string pName);

    std::string getConnectionString() const;
    std::string toBlueprint() const;
};

#endif //pole_H