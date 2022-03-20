#include "lexemes.h"

#include "exceptions.h"

Expression* Expression::parse(Lexer& lex){
    Expression *res = new Expression;
    res->left = Term::parse(lex);

    Token& curr = lex.current();
    
    //Have we reached the end of the stream?
    if(curr.isEOF()){
        //Eof reached, return
        Expression *opt = res->left;
        res->left = NULL;
        delete res;
        return opt;
    }

    if(curr == '+')
        res->op = PLUS;
    else if(curr == '-')
        res->op = MINUS;
    else if(curr == '&')
        res->op = AND;
    else if(curr == "|")
        res->op = OR;
    else if(curr == "^")
        res->op = XOR;
    else{
        //We may have reached a higher order operator, or invalid syntax
        Expression *opt = res->left;
        res->left = NULL;
        delete res;
        return opt;
    }

    res->right = Expression::parse(lex);

    return res;
}