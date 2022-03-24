#include "structureLexemes.h"

#include "exceptions.h"

std::ostream& dotConnection(std::ostream& os, const void *from, const void *to){
    return os << "\"" << from << "\" -> \"" << to << "\";\n"; 
}

std::ostream& dotNode(std::ostream& os, const void *obj, const char *label, const char *style){
    os << "\"" << obj << "\" [label=\"" << label << "\"";
    if(style != NULL)
        os << "," << style;
    
    return os << "];\n";
}

ValueExpression* Expression::parse(Lexer& lex){
    Expression *res = new Expression;
    res->left = Term::parse(lex);

    Token& curr = lex.current();
    
    //Have we reached the end of the stream?
    if(lex.eof()){
        //Eof reached, return
        ValueExpression *opt = res->left;
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
        ValueExpression *opt = res->left;
        res->left = NULL;
        delete res;
        return opt;
    }

    lex.consume();

    res->right = Expression::parse(lex);

    return res;
}

std::ostream& Expression::printDot(std::ostream& os) const {
    os << "\"" << this << "\" [label=\"Binary ";
    switch(op){
        case PLUS: os << '+'; break;
        case MINUS: os << '-'; break;
        case AND: os << '&'; break;
        case OR: os << '|'; break;
        case XOR: os << '^'; break;
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
