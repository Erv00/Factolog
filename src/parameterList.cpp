#include "structureLexemes.h"

#include "exceptions.h"
#include "autoDtor.h"

ParameterList* ParameterList::parse(Lexer& lex){
    ParameterList  *plist = new ParameterList();
    AutoDtor<ParameterList> dtor(plist);

    while(lex.current() != ")"){
        plist->parameters.push_back(Expression::parse(lex));

        if(lex.current() != ")")
            lex.except(",");
    }

    if(plist->parameters.size() == 0){
        delete plist;
        throw EmptyParameterListError(lex.current());
    }

    dtor.success();    
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

void ParameterList::checkSemantics(CompilationUnit& cu) const {
    for(size_t i=0; i<parameters.size(); i++)
        parameters[i]->checkSemantics(cu);
}
