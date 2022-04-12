#include "linkingUnit.h"

unsigned int LinkingUnit::getVariableColor(const Identifier& id) const {
    unsigned int a = variableColors.at(id);
    return a;
}

bool LinkingUnit::variableHasColor(const Identifier& id) const {
    std::map<const Identifier, unsigned int>::const_iterator it = variableColors.find(id);

    return it != variableColors.end();
}
