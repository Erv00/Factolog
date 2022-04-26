#include <iostream>
#include <fstream>

#include "compiler.h"
#include "exceptions.h"
#include "argumentParser.h"

int main(int argc, char* argv[]){
    try{
        Configuration conf(argc, argv);
        Compiler c(conf);
        c.compile();
    }catch (ParserError& p){
        std::cerr << "Parser error: " << p.what() << std::endl;
        return -1;
    }catch (ProgrammingError& p){
        std::cerr << "Programming error: " << p.what() << std::endl;
        return -1;
    }catch(const char* p){
        if(std::string(p) == "HELP") return -1;
        std::cerr << "Unexpected exception: " << p << std::endl;
    }

    return 0;
}
