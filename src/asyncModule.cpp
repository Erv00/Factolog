#include "modules.h"

#include "dot.h"
#include "autoDtor.h"
#include "exceptions.h"
#include "assignment.h"
#include "translator.h"
#include "compilationUnit.h"
#include "variableDeclaration.h"

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

void AsyncModule::calcualteColorTree(LinkingUnit* lu){
    for(size_t i=0; i<expressions.size(); i++){
        expressions[i]->calculateColorTree(lu);
    }
}

std::vector<AsyncExpression*> AsyncModule::linkModule(const Translator& translation) const{
    std::vector<AsyncExpression*> res;

    for(size_t i=0; i<expressions.size(); i++){
        AsyncExpression *aexp = expressions[i];

        AsyncExpression *clone = aexp->clone();
        clone->translate(translation);
        res.push_back(clone);
    }

    return res;
}

Module* AsyncModule::link(std::map<const Identifier, Module*>& modules) {
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
            const ParameterListDeclaration* expected = m->getParameters();

            std::map<Identifier, Identifier> trans;

            for(size_t ii=0; ii<expected->length(); ii++){
                const Parameter* p = expected->operator[](ii);
                const Identifier* id = dynamic_cast<const Identifier*>(list->operator[](ii));

                if(id == NULL){
                    std::cerr << "Cannot cast" << std::endl;
                    continue;
                }

                trans[*p->getIdentifier()] = *id;
            }

            std::vector<AsyncExpression*> newExpressions = mod->linkModule(Translator(trans));

            expressions.insert(expressions.end(),newExpressions.begin(), newExpressions.end());
            delete mc;
        }
    }

    return this;
}

EID AsyncModule::addToBlueprint(Blueprint& bp) const{
    for(size_t i=0; i<expressions.size(); i++)
        expressions[i]->addToBlueprint(bp);
    return 0;
}

std::vector<Identifier> AsyncModule::recalculateDefinedVariables(){
    std::vector<Identifier> res;
    for(size_t i=0; i<expressions.size(); i++){
        //Use a cast, or write a stupendous ammount of noop functions
        VariableDeclaration *vars = dynamic_cast<VariableDeclaration*>(expressions[i]);
        if(vars != NULL){
            std::vector<Identifier*> ids = vars->getDeclaredVariables();
            for(size_t ii=0; ii<ids.size(); ii++)
                res.push_back(Identifier(*(ids[ii])));
        }
    }

    for(size_t i=0; i<parameters->length(); i++){
        res.push_back(Identifier(*(parameters->operator[](i)->getIdentifier())));
    }

    return res;
}
