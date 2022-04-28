#include "exceptions.h"

#include "token.h"

#include <string.h>
#include <memtrace.h>

using namespace factolog;

TokenExpectedError::TokenExpectedError(Token expected, Token got){
    whatData = new char[17+10+expected.getContent().size()+got.getContent().size()+1];

    strcpy(whatData, "Expected symbol '");
    strcat(whatData, expected.getContent().c_str());
    strcat(whatData, "' but got ");
    strcat(whatData, got.getContent().c_str());
}

const char* ParserError::what() const throw(){
    return whatData;
}

const char* ProgrammingError::what() const throw(){
    return whatData;
}

UnexpectedSymbolError::UnexpectedSymbolError(Token got){
    whatData = new char[19+got.getContent().size()+1+1];

    strcpy(whatData, "Unexpected symbol '");
    strcat(whatData, got.getContent().c_str());
    strcat(whatData, "'");
}

ParserError::~ParserError() throw() {
    delete[] whatData;
}

ProgrammingError::~ProgrammingError() throw() {
    delete[] whatData;
}

EmptyParameterListError::EmptyParameterListError(Token t){
    whatData = new char[8+t.length()+20+1];

    strcpy(whatData, "Module '");
    strcat(whatData, t.getContent().c_str());
    strcat(whatData, "' has no connections");
}

ModuleAlreadyDefinedError::ModuleAlreadyDefinedError(Token identifier){
    whatData = new char[8+identifier.length()+21+1];

    strcpy(whatData, "Module '");
    strcat(whatData, identifier.getContent().c_str());
    strcat(whatData, "' was already defined");
}

UndefinedVariableError::UndefinedVariableError(const Identifier* var){
    std::string res = "Variable '";
    res = res + var->getName() + "' is not defined";

    whatData = new char[res.size()+1];
    strcpy(whatData, res.c_str());
}

VariableReassignmentError::VariableReassignmentError(const Identifier* var){
    std::string res = "Variable '";
    res = res + var->getName() + "' cannot be reassigned";

    whatData = new char[res.size()+1];
    strcpy(whatData, res.c_str());
}

ModuleNotDefinedError::ModuleNotDefinedError(const Identifier* module){
    std::string res = "Module '";
    res = res + module->getName() + "' is not defined";

    whatData = new char[res.size()+1];
    strcpy(whatData, res.c_str());
}

MismatchedParametersError::MismatchedParametersError(const Identifier* at){
    std::string res = "Mismatched parameters near '";
    res = res + at->getName() + "'";

    whatData = new char[res.size()+1];
    strcpy(whatData, res.c_str());
}

VariableAlreadyDefinedError::VariableAlreadyDefinedError(const Identifier* var){
    std::string res = "Variable '";
    res = res + var->getName() + "' is already defined";

    whatData = new char[res.size()+1];
    strcpy(whatData, res.c_str());
}
