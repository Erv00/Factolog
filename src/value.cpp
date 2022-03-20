#include "lexemes.h"

#include <ctype.h>
#include <sstream>


#include "exceptions.h"

Value* Value::parse(Lexer& lex){
    Token& curr = lex.current();
    if(isdigit(curr[0]))
        //Token is number
        return Number::parse(lex);
    else
        //Token must be identifier
        return Identifier::parse(lex);

}