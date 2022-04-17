#include "binaryExpression.h"

#include <map>
#include "number.h"
#include "blueprint.h"
#include "combinator.h"

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

void BinaryExpression::calculateColorTree(LinkingUnit* lu, unsigned int expectedOut){
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
        unsigned int leftCol = left->getOutColor(lu);
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
        unsigned int rightCol = right->getOutColor(lu);
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

void BinaryExpression::translate(const std::map<Identifier,Identifier>& translation){
    left->translate(translation);
    right->translate(translation);
}

EID BinaryExpression::addToBlueprint(Blueprint& bp) const{
    ArithmeticCombinator *ac = new ArithmeticCombinator(*this);
    switch(op){
        case PLUS:  ac->op = ArithmeticCombinator::PLUS;  break;
        case MINUS: ac->op = ArithmeticCombinator::MINUS; break;
        case AND:   ac->op = ArithmeticCombinator::AND;   break;
        case OR:    ac->op = ArithmeticCombinator::OR;    break;
        case XOR:   ac->op = ArithmeticCombinator::XOR;   break;
        case MUL:   ac->op = ArithmeticCombinator::MUL;   break;
        case DIV:   ac->op = ArithmeticCombinator::DIV;   break;
        case MOD:   ac->op = ArithmeticCombinator::MOD;   break;
        case LSHIFT:ac->op = ArithmeticCombinator::LSHIFT;break;
        case RSHIFT:ac->op = ArithmeticCombinator::RSHIFT;break;
        case EXP:   ac->op = ArithmeticCombinator::EXP;   break;
    }

    if(left->isConst())
        ac->setConst(LEFT, left->calculate());
    else if(right->isConst())
        ac->setConst(RIGHT, right->calculate());

    EID eid = bp.addEntity(ac);



    EID leftComb = left->addToBlueprint(bp);
    EID rightComb = right->addToBlueprint(bp);

    //We added another combinator while adding left
    bp.connect(leftComb, eid);

    //We added another combinator while adding right
    bp.connect(rightComb, eid);
    
    return eid;

}
