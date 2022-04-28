#include <gtest_lite.h>
#include <memtrace.h>

#include "blueprint.h"
#include "arithmeticCombinator.h"
#include "lexer.h"

#include <sstream>

using namespace factolog;

void blueprint_test() {
    std::stringstream ss("async module foo(in a){}");
    Lexer lex(ss);
    
    lex();

    AsyncModule *mod = AsyncModule::parse(lex);

    Blueprint bp(10, 1,"dummy", mod);

    TEST(Blueprint, Fitting){
        EXPECT_TRUE(bp.canCombinatorFit(Position(0,0)));
        ArithmeticCombinator *ac = new ArithmeticCombinator;
        ac->setPos(0,0);
        bp.addEntity(ac);
        EXPECT_FALSE(bp.canCombinatorFit(Position(0,0)));
    }END;

    delete mod;
}
