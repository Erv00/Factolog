#include <iostream>
#include <fstream>

#include "compiler.h"
#include "exceptions.h"

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout << "No files. Terminating" << std::endl;
        return -1;
    }


    Compiler c(argv[1], std::cout);
    try{
        c.compile();
    }catch (ParserError& p){
        std::cerr << "Parser error: " << p.what() << std::endl;
        return -1;
    }catch (ProgrammingError& p){
        std::cerr << "Programming error: " << p.what() << std::endl;
        return -1;
    }catch(const char* p){
        std::cerr << "Unexpected exception: " << p << std::endl;
    }

    return 0;
}
