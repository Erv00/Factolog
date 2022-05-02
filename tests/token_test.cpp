#include "gtest_lite.h"
#include "memtrace.h"

#include "token.h"

using namespace factolog;

void token_test() {
    TEST(Token, BasicCMP){
        Token t1("dummy"), t2("dummy2");
        EXPECT_NE(t1,t2);

        t2 = "dummy";
        EXPECT_EQ(t1,t2);
    }END;
}
