#include <gtest_lite.h>
#include <memtrace.h>

#include "arithmeticCombinator.h"

using namespace factolog;

void arithmeticCombinator_test() {
    TEST(ArithmeticCombinator, ControlString){
        ArithmeticCombinator ac;
        ac.op = ArithmeticCombinator::PLUS;

        EXPECT_STREQ("\"+\"", ac.getOperationString().c_str());
    }END;
}
