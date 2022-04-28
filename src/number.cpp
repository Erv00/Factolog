#include "number.h"

#include "exceptions.h"

#include <sstream>

using namespace factolog;

Number* Number::parse(Lexer& lex){
    Token& curr = lex.current();
    std::stringstream ss(curr);

    unsigned value;
    ss >> value;
    if(!ss.eof())
        //Didn't consume whole string, not a valid number
        throw UnexpectedSymbolError(curr);
    
    //Check bounds
    if(value > 2147483647u)
        //Out of bounds
        throw UnableToRepresentError();
    
    lex.consume();
    
    return new Number(value);
}

std::ostream& Number::printDot(std::ostream& os) const {
    return os << "\"" << this << "\" [label=\"" << value << "\"];\n";
}
