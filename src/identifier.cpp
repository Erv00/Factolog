#include "identifier.h"

#include "exceptions.h"
#include "compilationUnit.h"
#include "linkingUnit.h"
#include "translator.h"

Identifier* Identifier::parse(Lexer& lex){
    Token tok = lex.current();

    //TODO: CHEKC FOR END

    if(tok[0] != '_' && !isalpha(tok[0]))
        throw UnexpectedSymbolError(tok);
    
    for(size_t i=1;i<tok.length();i++)
        if(!isalnum(tok[i]) && tok[i] != '_')
            throw UnexpectedSymbolError(tok);
    
    //Token is valid identifier
    lex.consume();

    return new Identifier(tok);
    
}

void Identifier::calculateColorTree(LinkingUnit* lu, unsigned int expected){
    if(!lu->variableHasColor(*this))
        throw "Identifier has no color";
    setOutColor(lu->getVariableColor(*this));
    if(expected != getOutColor(lu))
        //Mismatch
        std::cout << "Color mismatch" << std::endl;
}

bool Identifier::hasOutColor(LinkingUnit* lu) const{
    if(getOutColor(lu) != 0)
        return true;
    return lu->variableHasColor(*this);
}

unsigned int Identifier::getOutColor(LinkingUnit* lu) const {
    if(outColor != 0)
        return outColor;
    return lu->getVariableColor(*this);
}

std::ostream& Identifier::printDot(std::ostream& os) const {
    return os << "\"" << this << "\" [label=\"" << name << "\"]\n";
}

void Identifier::checkSemantics(CompilationUnit& cu) const {
    if(!cu.isVariableDefined(this))
        throw UndefinedVariableError(this);
    
    if(!cu.isVariableAssigned(this))
        //TODO: Emit warning formally
        std::cerr << "Variable '" << name << "' uses default 0" << std::endl;
}

void Identifier::translate(const Translator& translation){
        name = translation.at(name).name;
}
