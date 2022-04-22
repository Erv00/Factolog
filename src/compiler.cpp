#include "compiler.h"

#include "blueprint.h"
#include "exceptions.h"
#include "linkingUnit.h"

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
    
    for(std::map<const Identifier, CompilationUnit*>::iterator it = compilationUnits.begin(); it != compilationUnits.end(); it++)
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
        CompilationUnit *cu = new CompilationUnit(definedModules);
        compilationUnits[it->first] = cu;
        it->second->checkSemantics(*cu);
    }
}

void Compiler::optimize(){
    for(std::map<const Identifier, Module*>::iterator it=definedModules.begin(); it != definedModules.end(); it++)
        it->second->optimize();
}

std::string Compiler::compileBlueprint() {
    AsyncModule* main = dynamic_cast<AsyncModule*>(definedModules[Identifier("main")]);

    if(main == NULL) throw "No main module defined";
    
    main->link(definedModules);

    std::vector<Identifier> ids =  main->recalculateDefinedVariables();
    LinkingUnit lu(ids.begin(), ids.end());
    unsigned int a = 5;
    main->calcualteColorTree(&lu, &a, NULL);

    Blueprint bp(18, 2, "substation", main);

    main->addToBlueprint(bp);

    std::stringstream ss;
    ss << bp;
    return ss.str();
}

void Compiler::compile(){
    lex();
    parse();
    check();
    optimize();


    std::string blueprintString = compileBlueprint();
    *os << blueprintString;
    //encode();
}
