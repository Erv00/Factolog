#include "unaryExpression.h"

#include "dot.h"
#include "value.h"
#include "autoDtor.h"
#include "blueprint.h"
#include "expression.h"
#include "arithmeticCombinator.h"

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
    lab += 'A'+getInColor(1);
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

void UnaryExpression::calculateColorTree(LinkingUnit* lu, unsigned int expected){
    //Unary exps never collide
    setOutColor(expected);
    
    //Check if input has color
    if(expr->hasOutColor(lu))
        //Input has color
        setInColor(expr->getOutColor(lu), RIGHT);
    else{
        //Input has no color, calculate
        setInColor(2, RIGHT);
        expr->calculateColorTree(lu, 2);
    }
}

void UnaryExpression::translate(const Translator& translation){
    expr->translate(translation);
}

EID UnaryExpression::addToBlueprint(Blueprint& bp) const{
    ArithmeticCombinator *ac = new ArithmeticCombinator(*this);

    switch(op){
        case PLUS:  ac->op = ArithmeticCombinator::PLUS;  break;
        case MINUS: ac->op = ArithmeticCombinator::MINUS; break;
        case NOT:   ac->op = ArithmeticCombinator::XOR;   break;
    }

    if(op != NOT)
        //Normal operation
        ac->setConst(LEFT, 0);
    else
        //Not <=> XOR
        ac->setConst(LEFT, /*2147483647u*/1);

    EID eid = bp.addEntity(ac);

    EID exprComb = expr->addToBlueprint(bp);

    //We added another combinator while adding left
    bp.connect(exprComb, eid);
    
    return eid;
}
