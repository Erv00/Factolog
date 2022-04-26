#include "factor.h"

#include "dot.h"
#include "autoDtor.h"
#include "unaryExpression.h"

#include <cmath>

ValueExpression* Factor::parse(Lexer& lex){
    Factor *res = new Factor;
    AutoDtor<Factor> dtor(res);

    res->left = UnaryExpression::parse(lex);

    Token& curr = lex.current();
    
    //Have we reached the end of the stream?
    if(lex.eof()){
        //Eof reached, return
        ValueExpression *opt = res->left;
        res->left = NULL;
        delete res;
        dtor.success();
        return opt;
    }

    if(curr == "**"){
        //Consume **
        lex.consume();
        res->right = Factor::parse(lex);
        dtor.success();
        return res;
    }else{
        //We may have reached a higher order operator, or invalid syntax
        ValueExpression *opt = res->left;
        res->left = NULL;
        delete res;
        dtor.success();
        return opt;
    }
} 

std::ostream& Factor::printDot(std::ostream& os) const {
    os << "\"" << this << "\" [label=\"Binary **\"]\n";
    if(left != NULL){
        left->printDot(os);
        std::string lab;
        lab += getInColor(0);
        dotConnection(os, this, left, lab.c_str());

        if(right != NULL){
            right->printDot(os);
            lab = getInColor(1);
            dotConnection(os, this, right, lab.c_str());
        }
    }else if(right != NULL)
        throw "Have right but no left";
    
    return os;
    
}

int Factor::calculate() const {
    if(!left->isConst() || !right->isConst())
        throw "To call calculate both left and right must be const";
    
    int l = left->calculate();
    int r = right->calculate();

    return std::pow(l,r);
}
