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

void BinaryExpression::calculateColorTree(unsigned int expectedOut){
    //Set own color
    setOutColor(expectedOut);

    if(left->hasOutColor() && right->hasOutColor()){
        //Both sides have out colors, preform sanity check
        //Maybe it can be optimized out?
        if(left->getOutColor() == right->getOutColor())
            //Left and right are the same
            //TODO: FIX, for now, throw error
            throw "Both inputs have same color";
        
        //Else all is good, set input color
        setInColor(left->getOutColor(), 0);
        setInColor(right->getOutColor(), 1);
    }else if(left->hasOutColor() && !right->hasOutColor()){
        //Left has color, right doesn't
        unsigned int leftCol = left->getOutColor();

        if(leftCol == 1)
            //Left color is 1, right should be 2
            right->calculateColorTree(2);
        else
            //Left's color is not in binary space
            right->calculateColorTree(1);
    }else if(!left->hasOutColor() && right->hasOutColor()){
        //Right has color, left doesn't
        unsigned int rightCol = right->getOutColor();

        if(rightCol == 1)
            //Right color is 1, left should be 2
            left->calculateColorTree(2);
        else
            //Right's color is not in binary space
            left->calculateColorTree(1);
    }else{
        //None have a color
        left->calculateColorTree(1);
        right->calculateColorTree(2);
    }
}
