#include "compiler.h"

#include "exceptions.h"
#include "linkingUnit.h"

using namespace factolog;

Compiler::Compiler(std::istream& _is, std::ostream& _os): is(&_is), os(&_os), ifs(NULL), ofs(NULL), doPrintBlueprint(true), doPrintDot(false){
    lexer = new Lexer(*is);
}
Compiler::Compiler(const char* filename, std::ostream& _os): os(&_os), ofs(NULL), doPrintBlueprint(true), doPrintDot(false){
    if(filename[0] == '-' && filename[1] == '\0'){
        //We want cin as input
        is = &std::cin;
        ifs = NULL;
    }else{
        ifs = new std::ifstream(filename);
        if(!ifs->is_open()){
            delete ifs;
            throw "UNABLE TO OPEN";
        }
        is = ifs;
    }
    lexer = new Lexer(*is);
}
Compiler::Compiler(const char* inFilename, const char* outFilename): doPrintBlueprint(true), doPrintDot(false){
    is = new std::fstream(inFilename, std::ios::in);
    os = new std::fstream(outFilename, std::ios::out);
    lexer = new Lexer(*is);
}

Compiler::Compiler(const Configuration& config){
    std::string filename = config.getInputFile();
    if(filename == "-"){
        //We want cin as input
        is = &std::cin;
        ifs = NULL;
    }else{
        ifs = new std::ifstream(filename.c_str());
        if(!ifs->is_open()){
            delete ifs;
            throw "UNABLE TO OPEN";
        }
        is = ifs;
    }

    filename = config.getOutFile();
    if(filename == "-" || filename == ""){
        //We want cout as output
        os = &std::cout;
        ofs = NULL;
    }else{
        ofs = new std::ofstream(config.getOutFile().c_str(), std::ios::out);
        if(!ofs->is_open()){
            delete ifs;
            delete ofs;
            throw "Unable to open output file";
        }
        os = ofs;
    }

    lexer = new Lexer(*is);

    doPrintBlueprint = config.printBlueprint();
    doPrintDot = config.printDot();
    userColorMapping = config.getSignals();
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

void Compiler::compile(){
    lex();
    parse();
    check();
    optimize();

    //Calculate colors
    Module *main = definedModules[Identifier("main")];
    if(main == NULL) throw "No main module defined";
    main->link(definedModules);
    std::vector<Identifier> ids =  main->recalculateDefinedVariables();
    std::vector<Color> colors;

    size_t i=0;
    for(; i<userColorMapping.size(); i++)
        colors.push_back(userColorMapping[i]);

    Color c = 3;
    for(; i<ids.size(); i++)
        colors.push_back(c++);

    LinkingUnit lu(ids.begin(), ids.end(), colors.begin(), colors.end());
    main->calcualteColorTree(&lu);

    if(doPrintBlueprint){
        throw "Thanos removed this";
    }
    if(doPrintDot) definedModules.at(Identifier("main"))->printDot(*os);

    //encode();
}
