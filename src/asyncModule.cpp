#include "modules.h"

#include "autoDtor.h"
#include "exceptions.h"
#include "dot.h"
#include "assignment.h"
#include "compilationUnit.h"

Module::~Module(){
    delete identifier;
    delete parameters;
}

AsyncModule* AsyncModule::parse(Lexer& lex){
    lex.except("async");
    lex.except("module");

    AsyncModule* amod = new AsyncModule();
    AutoDtor<AsyncModule> dtor(amod);

    amod->identifier = Identifier::parse(lex);

    lex.except("(");

    amod->parameters = ParameterListDeclaration::parse(lex);

    lex.except(")");
    lex.except("{");

    while(!lex.eof() && lex.current() != "}"){
        //Add expression
        amod->expressions.push_back(AsyncExpression::parse(lex));
    }

    lex.except("}");

    dtor.success();    
    return amod;
}

std::ostream& AsyncModule::printDot(std::ostream& os) const {
    os << "subgraph cluster_" << this << "{\nlabel=\"" << identifier->getName() << "\";\n";
    dotNode(os, this, identifier->getName().c_str(),"shape=box");

    if(parameters){
        parameters->printDot(os);
        dotConnection(os, this, parameters);
    }

    for(size_t i=0;i<expressions.size();i++){
        expressions[i]->printDot(os);
        dotConnection(os, this, expressions[i]);
    }

    os << "};\n";

    return os;
}

void AsyncModule::checkSemantics(CompilationUnit& cu) const {
    //Check parameters
    parameters->checkSemantics(cu);

    //Check all expressions
    for(size_t i=0; i<expressions.size(); i++)
        expressions[i]->checkSemantics(cu);
}

void AsyncModule::optimize(){
    for(size_t i=0; i<expressions.size(); i++)
        expressions[i]->optimize();
}

void AsyncModule::calcualteColorTree(LinkingUnit& lu, unsigned int expectedOut[], unsigned int inputs[]){
    (void)expectedOut;
    (void)inputs;
    for(size_t i=0; i<expressions.size(); i++){
        Assignment *a = dynamic_cast<Assignment *>(expressions[i]);
        if(a != NULL){
            a->calculateColorTree(lu);
        }
    }
}
