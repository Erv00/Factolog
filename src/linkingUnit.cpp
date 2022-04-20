#include "linkingUnit.h"

unsigned int LinkingUnit::getVariableColor(const Identifier& id) const {
    unsigned int a = variableColors.at(id);
    return a;
}

bool LinkingUnit::variableHasColor(const Identifier& id) const {
    std::map<const Identifier, unsigned int>::const_iterator it = variableColors.find(id);

    return it != variableColors.end();
}

void LinkingUnit::printVariableColorAssociation(std::ostream& os) const{
    for(std::map<const Identifier, unsigned int>::const_iterator it = variableColors.begin(); it != variableColors.end(); it++)
        os << it->first.getName() << ":\t" << (char)('A'+it->second-1) << std::endl;
}
