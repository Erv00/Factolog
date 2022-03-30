#include "asyncExpression.h"

#include "variableDeclaration.h"
#include "assignment.h"
#include "modules.h"

AsyncExpression* AsyncExpression::parse(Lexer& lex){
    //Determine what kind of expression follows
    if(lex.current() == "var")
        //Must be variable declaration
        return VariableDeclaration::parse(lex);
    else if(lex.next() == "=")
        //Must be assignment
        return Assignment::parse(lex);
    else
        //Should be module connection
        return ModuleConnection::parse(lex);
}
