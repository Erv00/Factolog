#include "unaryExpression.h"

#include "dot.h"
#include "value.h"
#include "autoDtor.h"
#include "expression.h"

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
        dtor.success();
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

    std::string lab;
    lab += 'A'+getInColor(0);
    dotConnection(os, this, expr, lab.c_str());

    return expr->printDot(os);
}

void UnaryExpression::checkSemantics(CompilationUnit& cu) const{
    expr->checkSemantics(cu);
}

void UnaryExpression::optimize() {
    //Do nothing
    //If it can be optimized, it will be done one layer up
    //If not we would just return anyway
}

int UnaryExpression::calculate() const {
    if(!expr->isConst())
        throw "To call calculate both left and right must be const";
    
    int val = expr->calculate();

    switch(op){
        case PLUS:  return val;
        case MINUS: return -val;
        case NOT:   return ~val;
        default:    return 0;
    }
}

void UnaryExpression::calculateColorTree(LinkingUnit& lu, unsigned int expected){
    //Unary exps never collide
    setOutColor(expected);
    
    //Check if input has color
    if(expr->hasOutColor(lu))
        //Input has color
        setInColor(expr->getOutColor(lu));
    else{
        //Input has no color, calculate
        setInColor(1);
        expr->calculateColorTree(lu, 1);
    }
}

void UnaryExpression::translate(const std::map<Identifier,Identifier>& translation){
    expr->translate(translation);
}
