#include "gtest_lite.h"
#include "identifierT.h"

#include <sstream>

void identifierT_test(){
    TEST(Identifier, ValidTest){
        std::stringstream in("foo");
        Lexer l(in);
        l();

        Identifier i(l);
        EXPECT_TRUE(i.match());
    }END;
    
    TEST(Identifier, ValidTest2){
        std::stringstream in("_f_o_o");
        Lexer l(in);
        l();

        Identifier i(l);
        EXPECT_TRUE(i.match());
    }END;
    
    TEST(Identifier, InvalidTest){
        std::stringstream in("2foo");
        Lexer l(in);
        l();

        Identifier i(l);
        EXPECT_FALSE(i.match());
    }END;
}