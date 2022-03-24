#include "structureLexemes.h"

ValueExpression* Factor::parse(Lexer& lex){
    Factor *res = new Factor;
    res->left = UnaryExpression::parse(lex);

    Token& curr = lex.current();
    
    //Have we reached the end of the stream?
    if(lex.eof()){
        //Eof reached, return
        ValueExpression *opt = res->left;
        res->left = NULL;
        delete res;
        return opt;
        return res;
    }

    if(curr == "**"){
        //Consume **
        lex.consume();
        res->right = Factor::parse(lex);
        return res;
    }else{
        //We may have reached a higher order operator, or invalid syntax
        ValueExpression *opt = res->left;
        res->left = NULL;
        delete res;
        return opt;
        return res;
    }
} 

std::ostream& Factor::printDot(std::ostream& os) const {
    os << "\"" << this << "\" [label=\"Binary **\"]\n";
    if(left != NULL){
        dotConnection(os, this, left);
        left->printDot(os);

        if(right != NULL){
            dotConnection(os, this, right);
            right->printDot(os);
        }
    }else if(right != NULL)
        throw "Have right but no left";
    
    return os;
    
}
