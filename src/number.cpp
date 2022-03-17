#include "lexemes.h"

#include "exceptions.h"

#include <sstream>

Number::Number(Lexer& l):Value(l){
    Token& curr = lex.current();
    std::stringstream ss(curr.c_str());

    ss >> value;
    if(!ss.eof())
        //Didn't consume whole string, not a valid number
        throw UnexpectedSymbolError(curr);
}
