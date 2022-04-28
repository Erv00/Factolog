#include "parameters.h"

#include "dot.h"
#include "autoDtor.h"
#include "exceptions.h"

using namespace factolog;

Parameter* Parameter::parse(Lexer& lex){
    Parameter *p = new Parameter();
    AutoDtor<Parameter> dtor(p);

    if(lex.current() == "in")
        p->direction = IN;
    else if(lex.current() == "out")
        p->direction = OUT;
    else
        throw UnexpectedSymbolError(lex.current());
    
    lex.consume();

    p->identifier = Identifier::parse(lex);

    dtor.success();
    return p;
}

std::ostream& Parameter::printDot(std::ostream& os) const{
    if(direction == IN)
        Dot::dotNode(os, this, ("In: "+identifier->getName()).c_str(), "");
    else
        Dot::dotNode(os, this, ("Out: "+identifier->getName()).c_str(), "");
    
    return os;
}
