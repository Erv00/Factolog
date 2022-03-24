#include "structureLexemes.h"

#include "exceptions.h"

ParameterList* ParameterList::parse(Lexer& lex){
    ParameterList  *plist = new ParameterList();

    while(lex.current() != ")"){
        plist->parameters.push_back(Expression::parse(lex));

        if(lex.current() != ")")
            lex.except(",");
    }

    if(plist->parameters.size() == 0){
        delete plist;
        throw EmptyParameterListError(lex.current());
    }

    return plist;
}

std::ostream& ParameterList::printDot(std::ostream& os) const{
    dotNode(os, this, "Params","");

    for(size_t i=0; i<parameters.size(); i++){
        parameters[i]->printDot(os);
        dotConnection(os, this, parameters[i]);
    }

    return os;
}
