#include "variableDeclaration.h"

#include "dot.h"
#include "autoDtor.h"
#include "exceptions.h"
#include "translator.h"
#include "compilationUnit.h"

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

VariableDeclaration::VariableDeclaration(const VariableDeclaration& vd){
    for(size_t i=0; i<vd.varsDeclared.size(); i++)
        varsDeclared.push_back(new Identifier(*(vd.varsDeclared[i])));
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

void VariableDeclaration::translate(const Translator& translation){
    for(size_t i=0; i<varsDeclared.size(); i++){
        Identifier *old = varsDeclared[i];
        Identifier *newID = new Identifier(translation.at(*old));
        varsDeclared[i] = newID;
        delete old;
    }
}
