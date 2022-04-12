#include "modules.h"

#include "dot.h"
#include "autoDtor.h"
#include "exceptions.h"
#include "compilationUnit.h"

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

void ModuleConnection::checkSemantics(CompilationUnit& cu) const {
    if(!cu.isModuleDefined(identifier))
        throw ModuleNotDefinedError(identifier);
    
    const ParameterListDeclaration* expectedParams = cu.getModuleParameters(identifier);

    if(expectedParams->length() != parameters->length())
        throw MismatchedParametersError(identifier);
    
    for(size_t i=0; i<expectedParams->length(); i++){
        switch((*expectedParams)[i]->getDirection()){
            case Parameter::IN:
                //Check semantics of incoming conn
                (*expectedParams)[i]->checkSemantics(cu);
                break;

            case Parameter::OUT:
                //Must be non assigned identifier
                const Identifier* id = dynamic_cast<const Identifier*>((*parameters)[i]);
                if(id == NULL)
                    //Not an identifier, invalid
                    throw "NOT AN LVALUE";//ModuleConnectionError;
                
                if(!cu.isVariableDefined(id))
                    throw UndefinedVariableError(id);
                
                if(cu.isVariableAssigned(id))
                    //Variable already assigned
                    throw VariableReassignmentError(id);
                    
                //We will need to define that variable after modul is ran
                //So the user cannot do foo(5, a, a+5), where a is not assigned
                break;
        }
    }

    //Mark OUT variables as assigned
    for(size_t i=0; i<expectedParams->length(); i++)
        if((*expectedParams)[i]->getDirection() == Parameter::OUT){
            const Identifier *id = dynamic_cast<const Identifier*>((*parameters)[i]);
            //Check not needed, was already checked before
            cu.assignVariable(id);
        }
}
