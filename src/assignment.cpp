#include "assignment.h"

#include "constantCombinator.h"
#include "compilationUnit.h"
#include "linkingUnit.h"
#include "expression.h"
#include "exceptions.h"
#include "blueprint.h"
#include "autoDtor.h"
#include "dot.h"

Assignment* Assignment::parse(Lexer& lex){
    Assignment *assign = new Assignment();
    AutoDtor<Assignment> dtor(assign);

    assign->to = Identifier::parse(lex);

    lex.except("=");

    assign->val = Expression::parse(lex);

    lex.except(";");

    dtor.success();    
    return assign;
}
std::ostream& Assignment::printDot(std::ostream& os) const{
    dotNode(os, this, "Assign", "");

    std::string lab;

    LinkingUnit lu((Identifier*)NULL, (Identifier*)NULL);

    lab += 'A' + val->getOutColor(NULL);

    to->printDot(os);
    dotConnection(os, this, to, lab.c_str());

    val->printDot(os);
    dotConnection(os, this, val, lab.c_str());

    return os;
}

void Assignment::checkSemantics(CompilationUnit& cu) const {
    if(!cu.isVariableDefined(to))
        throw UndefinedVariableError(to);
    
    if(cu.isVariableAssigned(to))
        throw VariableReassignmentError(to);
    
    val->checkSemantics(cu);

    cu.assignVariable(to);
}

void Assignment::calculateColorTree(LinkingUnit* lu){
    val->calculateColorTree(lu, lu->getVariableColor(*to));
}

AsyncExpression* Assignment::clone() const {
    Assignment *as = new Assignment;

    as->to = new Identifier(*to);
    as->val = val->clone();

    return as;
}

void Assignment::translate(const Translator& translation){
    to->translate(translation);
    val->translate(translation);
}

EID Assignment::addToBlueprint(Blueprint& bp) const{
    if(!val->isConst()){
        bp.connect(val->addToBlueprint(bp), 0);
        bp.openColumn();
        return 0;
    }else{
        ConstantCombinator *cc = new ConstantCombinator(val->getOutColor(NULL), val->calculate());
        EID eid = bp.addEntity(cc);
        bp.connect(eid, 0);
        bp.openColumn();
        return eid;
    }
}
