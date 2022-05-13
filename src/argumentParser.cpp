#include "argumentParser.h"
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string.h>

Configuration::Configuration(int argc, char *argv[]){
    //Set defaults
    _printDot = false;
    _printBlueprint = true;

    static struct option long_options[] = {
        {"dot",             no_argument,        0,  'd'},
        {"no-blueprint",    no_argument,        0,  'n'},
        {"output",          required_argument,  0,  'o'},
        {"help",            no_argument,        0,  'h'},
        {"signals",         required_argument,  0,  's'},
        {0,                 0,                  0,   0 }
    };
    static const char *optionHelp[] = {
        "Also print dot output",    //dot
        "Don't print factorio blueprint",   //no-blueprint
        "Write ouput to file instead of stdout",    //output
        "Display this help message",                //help
        "Use the specified signal mapping. Has the format of sig[, sig]..." //signals
    };
    int c;
    int optionIndex=0;
    std::string shortOpt = longOptionsToShort(long_options);
    optind = 0;
    while(true){
        c = getopt_long(argc, argv, shortOpt.c_str(), long_options, &optionIndex);

        if(c == -1) break;

        switch(c){
            case 'd': _printDot = true; break;
            case 'n': _printBlueprint = false; break;
            case 'o': outFile = optarg; break;
            case 'h':
                std::cerr << "Program to compile factolog programs\nUsage:\n" << argv[0] << " [options] file\nOptions:\n" << printOptions(long_options, optionHelp);
                throw "HELP";
            case 's': signals = parseTranslation(optarg); break;
            default: throw "Unknown option ";
        }
    }

    if(optind < argc) inputFile = argv[optind++];
    else throw "No input file. Terminating";

    for(;optind < argc; optind++)
        std::cerr << "Extraneous argument '" << argv[optind] << "'" << std::endl;
}

std::string Configuration::printOptions(const struct option options[], const char* help[]){
    //Get fill size
    size_t fillSize=0;
    for(size_t i=0; options[i].name != NULL; i++) if(strlen(options[i].name) > fillSize) fillSize = strlen(options[i].name)+2;

    std::stringstream ss;
    struct option opt=options[0];
    while(opt.name != NULL){
        int currFillSize = opt.has_arg ? fillSize-6 : fillSize;
        ss << "-" << (char)opt.val << " --" << std::left << std::setw(currFillSize) << opt.name << " ";
        if(opt.has_arg) ss << "[arg] ";
        ss << *(help++);
        ss << std::endl;
        options++;
        opt = *options;
    }

    return ss.str();
}

std::vector<std::string> Configuration::parseTranslation(const char* str){
    std::vector<std::string> result;
    std::string s = str;

    size_t start = 0;

    while(start < s.size()){
        size_t sep = s.find(',', start);
        if(sep != s.npos){
            //Found sep
            result.push_back(s.substr(start, sep-start));
            start = sep+1;
        }else{
            //No more sep, found last
            result.push_back(s.substr(start));
            break;
        }
    }

    //Trim
    for(size_t i=0; i<result.size(); i++){
        std::string s = result[i];
        s.erase(s.find_last_not_of(' ')+1);
        s.erase(0, s.find_first_not_of(' '));
        result[i] = s;
    }

    return result;
}

std::string Configuration::longOptionsToShort(const struct option long_options[]){
    std::stringstream ss;
    struct option opt = long_options[0];
    long_options++;
    while(opt.name != NULL){
        ss << (char)opt.val;
        if(opt.has_arg != 0) ss << ":";
        opt = *(long_options++);
    }
    std::string res = ss.str();
    return res;
}
