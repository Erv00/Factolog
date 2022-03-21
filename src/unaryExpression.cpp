#include "lexemes.h"

ValueExpression* UnaryExpression::parse(Lexer& lex){
    Token& curr = lex.current();

    UnaryExpression* res = new UnaryExpression();

    if(curr == "+"){
        res->op = UnaryExpression::PLUS;
        lex.consume();
    }else if(curr == "-"){
        res->op = UnaryExpression::MINUS;
        lex.consume();
    }else if(curr == "~"){
        res->op = UnaryExpression::NOT;
        lex.consume();
    }

    curr = lex.current();

    if(curr == "("){
        //( expression )
        lex.consume();
        res->expr = Expression::parse(lex);
        //throw "NABAZDMEG";
        lex.except(")");
        
        //No need to do unary +, it does nothing 
        if(res->op == PLUS)
            return res->expr;
        return res;
    }

    res->expr = Value::parse(lex);
    return res;
    
}