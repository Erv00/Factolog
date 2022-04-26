#include "valueExpression.h"


Color ValueExpression::getInColor(size_t index) const{
    return inColors[index];
}

bool ValueExpression::hasInColor(size_t index) const{
    return getInColor(index) != 0;
}

void ValueExpression::setInColor(Color col, size_t index){
    inColors[index] = col;
}
