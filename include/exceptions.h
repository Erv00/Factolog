#ifndef exceptions_H
#define exceptions_H

#include <exception>

class ParserError : std::exception::exception {};

class TokenExpectedError : ParserError {
    const char* what(){
        return "FOFOFO";
    }
};

class UnexpectedSymbolError : ParserError {
    public:
    UnexpectedSymbolError(Token);
};

#endif //exceptions_H