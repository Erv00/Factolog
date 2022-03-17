#include "lexemes.h"

#include <ctype.h>
#include <sstream>


#include "exceptions.h"

Value::Value(Lexer& l):Matcher(l){
    Token& curr = lex.current();
    if(isdigit(curr[0])){
        //Token is number
        return Number(l);
    }


}