#include "gtest_lite.h"
#include "memtrace.h"

#include "position.h"

using namespace factolog;

void position_test() {
    TEST(Position, plus){
        Position p1(0,0);
        EXPECT_EQ(p1.x, 0.0f);
        EXPECT_EQ(p1.y, 0.0f);

        Position p2 = p1 + Position(1,-1);
        EXPECT_EQ(p2.x, 1.0f);
        EXPECT_EQ(p2.y, -1.0f);

        p2 += Position(1, -1);
        EXPECT_EQ(p2.x, 2.0f);
        EXPECT_EQ(p2.y, -2.0f);
    }END;
}
