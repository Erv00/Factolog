#include "lexemes.h"

#include "exceptions.h"

Parameter* Parameter::parse(Lexer& lex){
    Parameter *p = new Parameter();

    if(lex.current() == "in")
        p->direction = IN;
    else if(lex.current() == "out")
        p->direction = OUT;
    else
        throw UnexpectedSymbolError(lex.current());
    
    lex.consume();

    p->identifier = Identifier::parse(lex);

    return p;
}

std::ostream& Parameter::printDot(std::ostream& os) const{
    if(direction == IN)
        dotNode(os, this, ("In: "+identifier->getName()).c_str(), "");
    else
        dotNode(os, this, ("Out: "+identifier->getName()).c_str(), "");
    
    return os;
}
