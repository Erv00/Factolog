#ifndef matcher_H
#define matcher_H

#include "lexer.h"

class Matcher {
    protected:
    Lexer& lex;
    public:
    /**
     * @brief Új Matcher létrehozása
     * 
     * @param l A használt lexer
     */
    Matcher(Lexer& l): lex(l){}    
};

#endif //matcher_H