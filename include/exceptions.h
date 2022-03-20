#ifndef exceptions_H
#define exceptions_H

#include <exception>
#include "lexer.h"

class ParserError : std::exception::exception {};

class TokenExpectedError : ParserError {
    const char* what(){
        return "FOFOFO";
    }
};


class UnexpectedSymbolError : public ParserError {
    public:
    UnexpectedSymbolError(Token a):ParserError(){
        a.length();
    }
    UnexpectedSymbolError(Token expected, Token got){
        expected.isEOF();
        got.isEOF();
    }
};

class UnableToRepresentError : ParserError {};
#endif //exceptions_H