#include "gtest_lite.h"
#include "memtrace.h"

#include "color.h"

using namespace factolog;

void color_test() {
    TEST(Color, Constructors){
        Color c1(0);
        EXPECT_STREQ("signal-@", c1.operator std::string().c_str());

        Color c2("dum:my");
        EXPECT_STREQ("my", c2.operator std::string().c_str());
    }END;

    TEST(Color, ==){
        Color c1("c:1");
        Color c2("c:2");
        EXPECT_NE(c1,c2);

        Color c3 = c1;
        EXPECT_EQ(c1, c3);
    }END;

    TEST(Color, ++){
        Color constCol(420);
        EXPECT_EQ(420u, constCol.toConst());
        EXPECT_EQ(420u, (constCol++).toConst());
        EXPECT_EQ(421u, constCol.toConst());

        Color col("virtual:A");
        EXPECT_STREQ("A", col.operator std::string().c_str());
        EXPECT_STREQ("A", (col++).operator std::string().c_str());
        EXPECT_STREQ("B", (col++).operator std::string().c_str());
    }END;
}
