#include "gtest_lite.h"

#include "compiler.h"
#include <sstream>
#include "memtrace.h"

void compiler_test(){
    TEST(Compiler, Basic){
        std::stringstream out;
        Compiler c("tests/compiler.fl", out);
        c.printBlueprintFlag() = false;
        c.printDotFlag() = true;
        EXPECT_NO_THROW(c.compile());

        //Check that all signals got assigned
        size_t pos = out.str().find_first_of('@');
        EXPECT_EQ(out.str().npos, pos);
    }END;
}
