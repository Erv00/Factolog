#include "compiler.h"

#include "exceptions.h"

Compiler::Compiler(std::istream& _is, std::ostream& _os): is(&_is), os(&_os), ifs(NULL), ofs(NULL){
    lexer = new Lexer(*is);
}
Compiler::Compiler(const char* filename, std::ostream& _os): os(&_os), ofs(NULL){
    if(filename[0] == '-' && filename[1] == '\0'){
        //We want cin as input
        is = &std::cin;
        ifs = NULL;
    }else{
        ifs = new std::ifstream(filename);
        if(!ifs->is_open())
            throw "UNABLE TO OPEN";
        is = ifs;
    }
    lexer = new Lexer(*is);
}
Compiler::Compiler(const char* inFilename, const char* outFilename){
    is = new std::fstream(inFilename, std::ios::in);
    os = new std::fstream(outFilename, std::ios::out);
    lexer = new Lexer(*is);
}

Compiler& Compiler::operator=(const Compiler& c){
    if(this==&c)
        return *this;

    if(lexer)
        delete lexer;
    
    is = c.is;
    os = c.os;
    lexer = new Lexer(*is);
    
    return *this;
}

Compiler::~Compiler(){
    for(std::map<const Identifier, Module*>::iterator it = definedModules.begin(); it != definedModules.end(); it++)
        delete it->second;
    delete lexer;

    delete ifs;
    delete ofs;
}

void Compiler::lex(){
    lexer->operator()();
}

void Compiler::parse(){
    while(!lexer->eof()){
        //Parse modules
        Module *mod = AsyncModule::parse(*lexer);

        if(definedModules.find(*mod->getIdentifier()) != definedModules.end()){
            //Module already defined
            std::string tok = mod->getIdentifier()->getName();
            delete mod;
            throw ModuleAlreadyDefinedError(tok);
        }
        
        definedModules[*mod->getIdentifier()] = mod;
    }
}

void Compiler::check(){
    for(std::map<const Identifier, Module*>::iterator it=definedModules.begin(); it != definedModules.end(); it++){
        CompilationUnit cu(definedModules);
        it->second->checkSemantics(cu);
    }
}

void Compiler::optimize(){
    for(std::map<const Identifier, Module*>::iterator it=definedModules.begin(); it != definedModules.end(); it++)
        it->second->optimize();
}

void Compiler::compile(){
    lex();
    parse();
    check();
    optimize();

    
    for(std::map<const Identifier, Module*>::iterator it=definedModules.begin(); it != definedModules.end(); it++){
        unsigned int a[] = {5};
        it->second->calcualteColorTree(a, NULL);
        it->second->printDot(std::cout);
    }

    //compileBlueprint();
    //encode();
}
