#include "expression.h"

#include "combinator.h"
#include "exceptions.h"
#include "blueprint.h"
#include "autoDtor.h"
#include "term.h"

std::ostream& dotConnection(std::ostream& os, const void *from, const void *to, const char *label=""){
    return os << "\"" << from << "\" -> \"" << to << "\" [label=\"" << label << "\"];\n"; 
}

std::ostream& dotNode(std::ostream& os, const void *obj, const char *label, const char *style){
    os << "\"" << obj << "\" [label=\"" << label << "\"";
    if(style != NULL)
        os << "," << style;
    
    return os << "];\n";
}

Expression::Expression(const Expression& e): BinaryExpression(e) {}

ValueExpression* Expression::clone() const {
    return new Expression(*this);
}

ValueExpression* Expression::parse(Lexer& lex){
    Expression *res = new Expression;
    AutoDtor<Expression> dtor(res);

    while(true){
        ValueExpression *t = Term::parse(lex);

        if(res->left == NULL)
            //Left is NULL, first item
            res->left = t;
        else if(res->right == NULL){
            //Filled both
            res->right = t;
            Expression *e = new Expression;
            dtor.update(e);
            e->left = res;
            res = e;
        }

        if(lex.eof()){
            //Reached end of stream
            ValueExpression *opt = res->left;
            res->left = NULL;
            delete res;
            dtor.success();
            return opt;
        }

        Token& curr = lex.current();
        
        if(curr == '+'){
            res->op = PLUS;
        }else if(curr == '-')
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
            dtor.success();
            return opt;
            break;
        }

        lex.consume();
    }

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
        default: throw "Invalid op";
    }

    os << "\"];\n";
    
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
        throw "Havbe right but no left";
    
    return os;
}

int Expression::calculate() const {
    if(!left->isConst() || !right->isConst())
        throw "To call calculate both left and right must be const";
    
    int l = left->calculate();
    int r = right->calculate();

    switch(op){
        case PLUS:  return l+r;
        case MINUS: return l-r;
        case AND:   return l&r;
        case OR:    return l|r;
        case XOR:   return l^r;
        default:    return 0;
    }
}
