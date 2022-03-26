#include "structureLexemes.h"

#include "autoDtor.h"

ValueExpression* Term::parse(Lexer& lex){
    Term *res = new Term;
    AutoDtor<Term> dtor(res);    

    res->left = Factor::parse(lex);

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
    }

    lex.consume();

    res->right = Term::parse(lex);

    dtor.success();
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
