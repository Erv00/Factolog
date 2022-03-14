#include "memtrace.h"
#include "lexer.h"

#include <limits>

bool isSingleCharToken(const char c);

Lexer::Lexer(istream& _is): is(_is){}

Lexer::Lexer(std::ifstream& _is): is(_is){
    if(!_is.is_open())
        throw "Unable to open file";
}

/*void Lexer::operator()(){
    //Read whole file and strip comments
    string content;
    std::noskipws(is);
    char prev = 'A';
    char c;
    
    while(is >> c){
        if(c == '#'){
            //Comment, skip to end of line
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }else if(c == '\n'){
            //Skip
        }else if(c == ' ' && prev == ' '){
            //Skip
        }else{
            content += c;
        }
        prev = c;
    }

    tokens.push_back(content);
}*/

void Lexer::operator()(){
    string current;
    string line;

    //std::noskipws(is);

    while(std::getline(is, line)){
        //Remove indentation
        size_t start = line.find_first_not_of(' ');
        if(start != line.npos && start != 0)
            line = line.substr(start);
        else if(start == line.npos)
            //Whole line is spaces
            continue;
        start = line.find_first_not_of('\t');
        if(start != line.npos && start != 0)
            line = line.substr(start);
        else if(start == line.npos)
            //Whole line is tabs
            continue;
        
        //Line is empty
        if(line.empty()) continue;
        
        //Remove comment
        if(line.length() >= 2 && line[0] == '/' && line[1] == '/'){
            //Starts with comment, disregard
            continue;
        }
        lexLine(line);
    }

    currentToken = tokens.begin();
    nextToken = currentToken+1;

}

void Lexer::lexLine(string line){
    string current;

    for(string::iterator it = line.begin(); it != line.end(); it++){
        //Check if single token
        if(isSingleCharToken(*it)){
            //Char is single token, save prev as token
            if(!current.empty()){
                tokens.push_back(current);
                current.clear();
            }

            //Also save SCT
            tokens.push_back(string(1,*it));
        }else if(*it != ' '){
            //Char is not a SCT, and not a space => add to current token
            current += *it;
        }else{
            //Got space => push current token, and ignore
            if(!current.empty()){
                tokens.push_back(current);
                current.clear();
            }
        }
    }

    //Reached end, push last token
    if(!current.empty())
        tokens.push_back(current);
}

Token& Lexer::current() const {
    return *currentToken;
}

void Lexer::consume(){
    currentToken = nextToken;
    if(nextToken != tokens.end())
        nextToken++;
}

std::ostream& operator<<(std::ostream& os, const Lexer& l){
    for(unsigned int i=0;i<l.getTokens().size(); i++){
        os << l.getTokens()[i] << "#";
    }
    return os;
}
bool isSingleCharToken(const char c){
    const char SCTs[] = "(){};," 
                        "="     
                        "!"    
                        "&|"    
                        "+-*/%^"  
                        "<>";
    
    for(size_t i=0; i<sizeof(SCTs); i++)
        if(SCTs[i] == c) return true;
    
    return false;
}