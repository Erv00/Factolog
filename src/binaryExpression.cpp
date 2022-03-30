#include "binaryExpression.h"

#include "number.h"

void BinaryExpression::optimize() {
    bool leftConst = left->isConst();
    bool rightConst = right->isConst();

    if(leftConst && rightConst)
        //Don't optimize, will be optimized one layer up
        return;
    if(leftConst){
        //Left is const
        int leftVal = left->calculate();
        delete left;
        left = new Number(leftVal);
    }else
        //Recurese down
        left->optimize();
    if(rightConst){
        //Right is const
        int rightVal = right->calculate();
        delete right;
        right = new Number(rightVal);
    }else
        //Recurse down
        right->optimize();
}
