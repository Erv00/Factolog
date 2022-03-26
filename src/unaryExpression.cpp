#include "structureLexemes.h"
#include "autoDtor.h"

ValueExpression* UnaryExpression::parse(Lexer& lex){
    Token& curr = lex.current();

    UnaryExpression* res = new UnaryExpression();
    AutoDtor<UnaryExpression> dtor(res);    

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
        lex.except(")");
        
        //No need to do unary +, it does nothing 
        if(res->op == PLUS){
            ValueExpression *expr = res->expr;
            res->expr = NULL;
            delete res;
            dtor.success();
            return expr;
        }
        return res;
    }

    res->expr = Value::parse(lex);

    //No need to do unary +, it does nothing 
    if(res->op == PLUS){
        ValueExpression* expr = res->expr;
        res->expr = NULL;
        delete res;
        dtor.success();
        return expr;
    }
    dtor.success();
    return res;
    
}

std::ostream& UnaryExpression::printDot(std::ostream& os) const {
    os << "\"" << this << "\" [label=\"Unary ";
    switch(op){
        case MINUS:
            os << '-';
            break;
        case NOT:
            os << '~';
            break;
        case PLUS:
            throw "Unary + not optimized";
    }

    os << "\"]\n";

    os << "\"" << this << "\" -> \"" << expr << "\";\n";

    return expr->printDot(os);
}
