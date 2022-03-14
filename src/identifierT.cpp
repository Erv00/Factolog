#include "identifierT.h"

#include "exceptions.h"

Identifier::Identifier(Lexer& l):Matcher(l){}

bool Identifier::match(){
    Token tok = lex.current();

    //TODO: CHEKC FOR END

    if(tok[0] != '_' && !isalpha(tok[0]))
        return false;
    
    for(size_t i=1;i<tok.length();i++)
        if(!isalnum(tok[i]) && tok[i] != '_')
            return false;
    
    //Token is valid identifier
    lex.consume();
    return true;
}