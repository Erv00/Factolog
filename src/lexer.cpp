#include "memtrace.h"
#include "lexer.h"

#include "exceptions.h"

#include <limits>

using namespace factolog;

Token Lexer::END_TOKEN("");

Lexer::Lexer(std::istream& _is): is(_is){}

Lexer::Lexer(std::ifstream& _is): is(_is){
    if(!_is.is_open())
        throw "Unable to open file";
}

void Lexer::operator()(){
    std::string current;
    std::string line;

    while(std::getline(is, line)){
        //Remove comment
        size_t commentBegin = line.find_first_of("//");
        if(commentBegin != line.npos){
            //Found a /
            if(commentBegin != line.size()-1){
                // / is not the last
                if(line[commentBegin+1] == '/'){
                    //Next is also /, found comment
                    line = line.erase(commentBegin);
                }
            }
        }

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
        
        lexLine(line);
    }

    currentToken = tokens.begin();
    nextToken = currentToken+1;

}

void Lexer::lexLine(std::string line){
    std::string current;

    for(std::string::iterator it = line.begin(); it != line.end(); it++){
        //Check if 2 char token
        if(isTwoCharToken(it)){
            //Current and next char form a 2CT, save prev as token
            if(!current.empty()){
                tokens.push_back(current);
                current.clear();
            }

            //Also save 2CT
            tokens.push_back(std::string(2,*it));

            //Also consume 2nd char
            it++;
        }else if(isSingleCharToken(*it)){     //Check if single token
            //Char is single token, save prev as token
            if(!current.empty()){
                tokens.push_back(current);
                current.clear();
            }

            //Also save SCT
            tokens.push_back(std::string(1,*it));
        }else if(*it != ' ' && *it != '\t'){
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
    if(currentToken == tokens.end()) return END_TOKEN;
    return *currentToken;
}

Token& Lexer::next() const {
    if(nextToken == tokens.end()) return END_TOKEN;
    return *nextToken;
}

void Lexer::except(Token t){
    if(eof())
        throw TokenExpectedError(t, Token("EOF"));
    if(t != current())
        throw TokenExpectedError(t, current());
    consume();
}

void Lexer::consume(){
    currentToken = nextToken;
    if(nextToken != tokens.end())
        nextToken++;
}

bool Lexer::eof() const {
    return currentToken == tokens.end();
}

std::ostream& factolog::operator<<(std::ostream& os, const Lexer& l){
    for(unsigned int i=0;i<l.getTokens().size(); i++){
        os << l.getTokens()[i] << "#";
    }
    return os;
}
bool Lexer::isSingleCharToken(char c) const{
    const char SCTs[] = "(){};," 
                        "="     
                        "!"    
                        "&|"    
                        "+-*/%^"  
                        "~";
    
    for(size_t i=0; i<sizeof(SCTs); i++)
        if(SCTs[i] == c) return true;
    
    return false;
}

bool Lexer::isTwoCharToken(std::string::iterator& it) const{
    if(*it != *(it+1)) return false;

    //The next 2 chars are the same
    switch(*it){
        case '*': return true;
        case '<': return true;
        case '>': return true;
        default : return false;
    }
}
