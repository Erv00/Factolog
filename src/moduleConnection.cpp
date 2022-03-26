#include "structureLexemes.h"

#include "autoDtor.h"

ModuleConnection* ModuleConnection::parse(Lexer& lex){
    ModuleConnection *mc = new ModuleConnection();
    AutoDtor<ModuleConnection> dtor(mc);

    mc->identifier = Identifier::parse(lex);

    lex.except("(");
    mc->parameters = ParameterList::parse(lex);

    lex.except(")");
    lex.except(";");

    dtor.success();
    return mc;
}

std::ostream& ModuleConnection::printDot(std::ostream& os) const{
    dotNode(os, this, identifier->getName().c_str(), "shape=Msquare");

    parameters->printDot(os);

    dotConnection(os, this, parameters);

    return os;    
}
