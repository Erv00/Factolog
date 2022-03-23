#include "exceptions.h"

#include "token.h"

#include <string.h>
#include <memtrace.h>


TokenExpectedError::TokenExpectedError(Token expected, Token got){
    whatData = new char[16+9+expected.getContent().size()+got.getContent().size()+1];

    strcpy(whatData, "Expected symbol ");
    strcat(whatData, expected.getContent().c_str());
    strcat(whatData, " but got ");
    strcat(whatData, got.getContent().c_str());
}

const char* ParserError::what() const throw(){
    return whatData;
}

const char* ProgrammingError::what() const throw(){
    return whatData;
}

UnexpectedSymbolError::UnexpectedSymbolError(Token got){
    whatData = new char[19+got.getContent().size()+1];

    strcpy(whatData, "Unexpected symbol ");
    strcat(whatData, got.getContent().c_str());
}

ParserError::~ParserError() throw() {
    delete[] whatData;
}

ProgrammingError::~ProgrammingError() throw() {
    delete[] whatData;
}

EmptyParameterListError::EmptyParameterListError(Token t){
    whatData = new char[26+1];

    strcpy(whatData, "Module has no connections");

    t.isEOF();
}
