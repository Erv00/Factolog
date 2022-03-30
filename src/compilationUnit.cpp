#include "compilationUnit.h"

#include "parameters.h"

bool CompilationUnit::isVariableDefined(const Identifier* id) const {
    return definedVariables.find(*id) != definedVariables.end();
}

void CompilationUnit::defineVariable(const Identifier* id){
    definedVariables.insert(*id);
}

bool CompilationUnit::isVariableAssigned(const Identifier* id) const{
    return assignedVariables.find(*id) != assignedVariables.end();
}

void CompilationUnit::assignVariable(const Identifier* id){
    assignedVariables.insert(*id);
}

bool CompilationUnit::isModuleDefined(const Identifier* module) const{
    return definedModules.find(*module) != definedModules.end(); 
}


const ParameterListDeclaration* CompilationUnit::getModuleParameters(const Identifier* module) const{
    return definedModules.at(*module)->getParameters();
}
