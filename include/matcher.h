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

    /**
     * @brief Megpóbálja a lexertől érkező input streamet matchelni
     * 
     * Előrébb lépteti a lexer tokenstreamjét ha sikeres a match
     * 
     * @return true ha sikeres volt a match
     * @return false ha sikertelen volt a match
     */
    virtual bool match() = 0;  
};

#endif //matcher_H
