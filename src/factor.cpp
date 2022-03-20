#include "lexemes.h"

Factor* Factor::parse(Lexer& lex){
    Factor *res = new Factor;
    res->left = UnaryExpression::parse(lex);

    Token& curr = lex.current();
    
    //Have we reached the end of the stream?
    if(curr.isEOF()){
        //Eof reached, return
        /*Factor *opt = res->left;
        res->left = NULL;
        delete res;
        return opt;*/
        return res;
    }

    if(curr == "**")
        res->op = EXPONENT;
    else{
        //We may have reached a higher order operator, or invalid syntax
        /*Factor *opt = res->left;
        res->left = NULL;
        delete res;
        return opt;*/
        return res;
    }

    res->right = Factor::parse(lex);

    return res;

}