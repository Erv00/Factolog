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

void AsyncModule::calcualteColorTree(LinkingUnit* lu, unsigned int expectedOut[], unsigned int inputs[]){
    (void)expectedOut;
    (void)inputs;
    for(size_t i=0; i<expressions.size(); i++){
        //Only calculate color tree for assignment, as the oders make no sense
        Assignment *a = dynamic_cast<Assignment *>(expressions[i]);
        if(a != NULL){
            a->calculateColorTree(lu);
        }
    }
}

std::vector<AsyncExpression*> AsyncModule::linkModule(const std::map<Identifier,Identifier>& translation) const{
    std::vector<AsyncExpression*> res;

    for(size_t i=0; i<expressions.size(); i++){
        AsyncExpression *aexp = expressions[i];

        AsyncExpression *clone = aexp->clone();
        clone->translate(translation);
        res.push_back(clone);
    }

    return res;
}

AsyncModule* AsyncModule::link(std::map<const Identifier, Module*>& modules) {
    for(size_t i=0; i<expressions.size(); i++){
        ModuleConnection *mc = dynamic_cast<ModuleConnection*>(expressions[i]);

        if(mc != NULL){
            //Found module connection
            expressions.erase(expressions.begin() + i);
            i--;

            Module *m = modules.at(*mc->getIdentifier());
            AsyncModule *mod = dynamic_cast<AsyncModule*>(m);
            if(mod == NULL){
                std::cout << "Module not async?" << std::endl;
                continue;
            }

            ParameterList* list = mc->getParameters();
            ParameterListDeclaration* expected = mod->parameters;

            std::map<Identifier, Identifier> trans;

            for(size_t ii=0; ii<expected->length(); ii++){
                Parameter* p = expected->operator[](ii);
                const Identifier* id = dynamic_cast<const Identifier*>(list->operator[](ii));

                if(id == NULL){
                    std::cout << "Cannot cast" << std::endl;
                    continue;
                }

                trans[*p->getIdentifier()] = *id;
            }

            std::vector<AsyncExpression*> newExpressions = mod->linkModule(trans);

            expressions.insert(expressions.end(),newExpressions.begin(), newExpressions.end());
        }
        delete mc;
    }

    return this;
}

EID AsyncModule::addToBlueprint(Blueprint& bp) const{
    for(size_t i=0; i<expressions.size(); i++)
        expressions[i]->addToBlueprint(bp);
    return 0;
}
