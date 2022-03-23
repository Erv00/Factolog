#ifndef exceptions_H
#define exceptions_H

#include <exception>
#include <sstream>

#include "lexer.h"

class ParserError : public std::exception{
    protected:
    char *whatData;
    public:
    const char* what() const throw();
};

class TokenExpectedError : public ParserError {
    public:
    //const char* what();
    TokenExpectedError(Token expected, Token got);
    ~TokenExpectedError() throw() {};
};


class UnexpectedSymbolError : public ParserError {
    public:
    UnexpectedSymbolError(Token got);
    ~UnexpectedSymbolError() throw() {};
};

class UnableToRepresentError : ParserError {};

class ProgrammingError : public std::exception {
    protected:
    char *whatData;
};

class EmptyParameterListError : public ProgrammingError{
    public:
    EmptyParameterListError(Token t);
    ~EmptyParameterListError() throw();
    const char* what() const throw();
};
#endif //exceptions_H
