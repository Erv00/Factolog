#include "linkingUnit.h"

using namespace factolog;

Color LinkingUnit::getVariableColor(const Identifier& id) const {
    Color a = variableColors.at(id);
    return a;
}

bool LinkingUnit::variableHasColor(const Identifier& id) const {
    std::map<const Identifier, Color>::const_iterator it = variableColors.find(id);

    return it != variableColors.end();
}

void LinkingUnit::printVariableColorAssociation(std::ostream& os) const{
    for(std::map<const Identifier, Color>::const_iterator it = variableColors.begin(); it != variableColors.end(); it++)
        os << it->first.getName() << ":\t" << it->second << std::endl;
}
