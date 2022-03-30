#include "parameters.h"

#include "dot.h"
#include "autoDtor.h"
#include "exceptions.h"
#include "compilationUnit.h"

ParameterListDeclaration* ParameterListDeclaration::parse(Lexer& lex){
    
    ParameterListDeclaration *plistd = new ParameterListDeclaration();
    AutoDtor<ParameterListDeclaration> dtor(plistd);

    while(lex.current() == "in" || lex.current() == "out"){
        plistd->parameters.push_back(Parameter::parse(lex));

        if(lex.current() == ",")
            lex.consume();
    }

    if(plistd->parameters.size() == 0)
        throw EmptyParameterListError(lex.current());

    dtor.success();
    return plistd;
}

std::ostream& ParameterListDeclaration::printDot(std::ostream& os) const{
    dotNode(os, this, "Parameters", "");

    for(size_t i=0; i<parameters.size(); i++){
        parameters[i]->printDot(os);
        dotConnection(os, this, parameters[i]);
    }

    return os;
}

void ParameterListDeclaration::checkSemantics(CompilationUnit& cu) const {
    for(size_t i=0; i<parameters.size(); i++){
        Parameter *param = parameters[i];
        
        if(cu.isVariableDefined(param->getIdentifier()))
            throw VariableAlreadyDefinedError(param->getIdentifier());

        cu.defineVariable(param->getIdentifier());
        if(param->getDirection() == Parameter::IN){
            //Parameter is inbound, define and assign
            cu.assignVariable(param->getIdentifier());
        }
    }
}
