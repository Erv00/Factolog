#include <iostream>
#include <fstream>

#include "structureLexemes.h"
#include "exceptions.h"

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout << "No files. Terminating" << std::endl;
        return -1;
    }


    Lexer *l;
        std::fstream file(argv[1]);

    if(argv[1][0] == '-' && argv[1][1] == '\0'){
        l = new Lexer(std::cin);
    }else{


        if(!file.is_open()){
            std::cout << "File \"" << argv[1] << "\" could not be opened. Terminating" << std::endl;
            return -1;
        }
        l = new Lexer(file);
    }

    try{
        l->operator()();
        AsyncModule *amod = AsyncModule::parse(*l);

        std::cout << argv[1] << ":\ndigraph G {\n";
        amod->printDot(std::cout) << "}" << std::endl;

        delete amod;
    }catch (ParserError& p){
        std::cerr << "Parser error: " << p.what() << std::endl;
        return -1;
    }catch (ProgrammingError& p){
        std::cerr << "Programming error: " << p.what() << std::endl;
        return -1;
    }

    delete l;

    return 0;
}