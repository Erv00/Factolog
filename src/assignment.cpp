#include "structureLexemes.h"

#include "autoDtor.h"

Assignment* Assignment::parse(Lexer& lex){
    Assignment *assign = new Assignment();
    AutoDtor<Assignment> dtor(assign);

    assign->to = Identifier::parse(lex);

    lex.except("=");

    assign->val = Expression::parse(lex);

    lex.except(";");

    dtor.success();    
    return assign;
}
std::ostream& Assignment::printDot(std::ostream& os) const{
    dotNode(os, this, "Assign", "");

    to->printDot(os);
    dotConnection(os, this, to);

    val->printDot(os);
    dotConnection(os, this, val);

    return os;
}
