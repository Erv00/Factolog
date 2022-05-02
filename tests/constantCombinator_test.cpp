#include "gtest_lite.h"
#include "memtrace.h"

#include "constantCombinator.h"

using namespace factolog;

void constantCombinator_test() {
    TEST(ConstantCombinator, Basic){
        ConstantCombinator cc(std::string("dum:my"), 420);

        EXPECT_STREQ("\"control_behavior\":{\"filters\":[{\"signal\":{\"type\":\"dum\",\"name\":\"my\"},\"count\":420,\"index\":1}]}",cc.getControlString().c_str());
    }END;
}
