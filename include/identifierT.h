#ifndef identifierT_H
#define identifierT_H

#include "matcher.h"

class Identifier : Matcher{
    public:
    Identifier(Lexer&);
    bool match();
};

#endif //identifierT_H