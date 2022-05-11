#include "modules.h"

#include "dot.h"
#include "autoDtor.h"
#include "translator.h"
#include "exceptions.h"
#include "compilationUnit.h"

ModuleConnection::ModuleConnection(const ModuleConnection& mc){
    identifier = new Identifier(*mc.identifier);
    parameters = new ParameterList(*mc.parameters);
}

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
                //Parameter direction is OUT, this means it must be an identifier
                //Due to stroing also expression we need this check
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
            //We have already checked and given reasons for this casts existence
            const Identifier *id = static_cast<const Identifier*>((*parameters)[i]);
            //Check not needed, was already checked before
            cu.assignVariable(id);
        }
}

void ModuleConnection::translate(const Translator& translation){
    parameters->translate(translation);
}

std::vector<AsyncExpression*> ModuleConnection::linkExpression(const std::map<const Identifier, Module*>& modules, bool& doDelete){
    doDelete = true;
    Module *mod = modules.at(*this->identifier);

    ParameterList* list = this->getParameters();
    const ParameterListDeclaration* expected = mod->getParameters();

    std::map<Identifier, Identifier> trans;

    for(size_t ii=0; ii<expected->length(); ii++){
        const Parameter* p = expected->operator[](ii);
        //Need to cast to identifier, as we need to check that it is in fact an ID, and not an expression
        const Identifier* id = dynamic_cast<const Identifier*>(list->operator[](ii));

        if(id == NULL){
            std::cerr << "Cannot cast" << std::endl;
            continue;
        }

        trans[*p->getIdentifier()] = *id;
    }

    //This cast is needed, because we cannot assume it's type
    //We only have asnyc stuff now, so this is enough
    std::vector<AsyncExpression*> newExpressions = static_cast<AsyncModule*>(mod)->linkModule(Translator(trans));
    return newExpressions;
}
