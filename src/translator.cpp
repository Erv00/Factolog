#include "translator.h"

#include <sstream>

using namespace factolog;

unsigned int Translator::globalTranslationID = 0;

Identifier Translator::at(const Identifier& id) const {
    try{
        return trans.at(id);
    }catch(std::out_of_range&){
        //Variable is local, add uniqueness
        std::stringstream ss;
        ss << translationID << "$" << id.getName();
        return ss.str();
    }
}
