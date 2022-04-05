#include "term.h"

#include "dot.h"
#include "factor.h"
#include "autoDtor.h"

ValueExpression* Term::parse(Lexer& lex){
    Term *res = new Term;
    AutoDtor<Term> dtor(res);

    while(true){
        ValueExpression *t = Factor::parse(lex);


        if(res->left == NULL)
            //Left is NULL, first item
            res->left = t;
        else if(res->right == NULL){
            //Filled both
            res->right = t;
            Term *e = new Term;
            dtor.update(e);
            e->left = res;
            res = e;
        }

        Token& curr = lex.current();
        
        if(curr == '*')
            res->op = MUL;
        else if(curr == '/')
            res->op = DIV;
        else if(curr == '%')
            res->op = MOD;
        else if(curr == "<<")
            res->op = LSHIFT;
        else if(curr == ">>")
            res->op = RSHIFT;
        else{
            //We may have reached a higher order operator, or invalid syntax
            ValueExpression *opt = res->left;
            res->left = NULL;
            delete res;
            dtor.success();
            return opt;
            break;
        }

        lex.consume();
    }

    return res;

}
std::ostream& Term::printDot(std::ostream& os) const {
    os << "\"" << this << "\" [label=\"Binary ";
    switch(op){
        case MUL: os << '*'; break;
        case DIV: os << '/'; break;
        case MOD: os << '%'; break;
        case LSHIFT: os << "<<"; break;
        case RSHIFT: os << ">>"; break;
    }

    os << "\"];\n";
    
    if(left != NULL){
        left->printDot(os);
        dotConnection(os, this, left);

        if(right != NULL){
            right->printDot(os);
            dotConnection(os, this, right);
        }
    }else if(right != NULL)
        throw "Havbe right but no left";
    
    return os;
}

int Term::calculate() const {
    if(!left->isConst() || !right->isConst())
        throw "To call calculate both left and right must be const";
    
    int l = left->calculate();
    int r = right->calculate();

    switch(op){
        case MUL: return l*r;
        case DIV: return l/r;
        case MOD: return l%r;
        case LSHIFT: return l<<r;
        case RSHIFT: return l>>r;
        default:     return 0;
    }
}
