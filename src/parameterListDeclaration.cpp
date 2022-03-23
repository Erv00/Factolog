#include "lexemes.h"

#include "exceptions.h"

ParameterListDeclaration* ParameterListDeclaration::parse(Lexer& lex){
    
    ParameterListDeclaration *plistd = new ParameterListDeclaration();

    while(lex.current() == "in" || lex.current() == "out"){
        plistd->parameters.push_back(Parameter::parse(lex));

        if(lex.current() == ",")
            lex.consume();
    }

    if(plistd->parameters.size() == 0)
        throw EmptyParameterListError(lex.current());

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
