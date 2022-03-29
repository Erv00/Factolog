#include "structureLexemes.h"

#include "exceptions.h"
#include "autoDtor.h"

VariableDeclaration* VariableDeclaration::parse(Lexer& lex){
    lex.except("var");

    VariableDeclaration* va = new VariableDeclaration();
    AutoDtor<VariableDeclaration> dtor(va);

    va->varsDeclared.push_back(Identifier::parse(lex));

    while(!lex.eof() && lex.current() == ","){
        lex.except(',');
        va->varsDeclared.push_back(Identifier::parse(lex));
    }

    lex.except(";");

    if(va->varsDeclared.size() == 0)
        throw UnexpectedSymbolError(lex.current());
    
    dtor.success();
    return va;
}


std::ostream& VariableDeclaration::printDot(std::ostream& os) const{
    dotNode(os, this, "New vars", "");

    for(size_t i=0; i<varsDeclared.size(); i++){
        varsDeclared[i]->printDot(os);
        dotConnection(os, this, varsDeclared[i]);
    }

    return os;
}

void VariableDeclaration::checkSemantics(CompilationUnit& cu) const {
    //None of the variables can be defined
    for(size_t i=0; i<varsDeclared.size(); i++){
        if(cu.isVariableDefined(varsDeclared[i]))
            throw VariableAlreadyDefinedError(varsDeclared[i]);
        
        cu.defineVariable(varsDeclared[i]);
    }
}
