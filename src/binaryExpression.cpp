#include "binaryExpression.h"

#include <map>
#include "number.h"

using namespace factolog;

BinaryExpression::BinaryExpression(const BinaryExpression& b){
    left = b.left->clone();
    right = b.right->clone();
    op = b.op;
}

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

void BinaryExpression::calculateColorTree(LinkingUnit* lu, Color expectedOut){
    //Set own color
    setOutColor(expectedOut);

    if(left->hasOutColor(lu) && right->hasOutColor(lu)){
        //Both sides have out colors, preform sanity check
        //Maybe it can be optimized out?
        if(left->getOutColor(lu) == right->getOutColor(lu))
            //Left and right are the same
            //TODO: FIX, for now, throw error
            throw "Both inputs have same color";
        
        //Else all is good, set input color
        setInColor(left->getOutColor(lu), 0);
        setInColor(right->getOutColor(lu), 1);
    }else if(left->hasOutColor(lu) && !right->hasOutColor(lu)){
        //Left has color, right doesn't
        Color leftCol = left->getOutColor(lu);
        setInColor(leftCol, LEFT);

        if(leftCol == 1){
            //Left color is 1, right should be 2
            right->calculateColorTree(lu, 2);
            setInColor(2, RIGHT);
        }else{
            //Left's color is not in binary space
            right->calculateColorTree(lu, 1);
            setInColor(1, RIGHT);
        }
    }else if(!left->hasOutColor(lu) && right->hasOutColor(lu)){
        //Right has color, left doesn't
        Color rightCol = right->getOutColor(lu);
        setInColor(rightCol, RIGHT);

        if(rightCol == 1){
            //Right color is 1, left should be 2
            left->calculateColorTree(lu, 2);
            setInColor(2, LEFT);
        }else{
            //Right's color is not in binary space
            left->calculateColorTree(lu, 1);
            setInColor(1, LEFT);
        }
    }else{
        //None have a color
        left->calculateColorTree(lu, 1);
        right->calculateColorTree(lu, 2);
        setInColor(1,LEFT);
        setInColor(2, RIGHT);
    }
}

void BinaryExpression::translate(const Translator& translation){
    left->translate(translation);
    right->translate(translation);
}
