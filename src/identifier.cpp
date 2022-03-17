#include "lexemes.h"

#include "exceptions.h"

Identifier::Identifier(Lexer& l):Matcher(l){
    Token tok = lex.current();

    //TODO: CHEKC FOR END

    if(tok[0] != '_' && !isalpha(tok[0]))
        throw UnexpectedSymbolError();
    
    for(size_t i=1;i<tok.length();i++)
        if(!isalnum(tok[i]) && tok[i] != '_')
            throw UnexpectedSymbolError();
    
    //Token is valid identifier
    lex.consume();
}

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