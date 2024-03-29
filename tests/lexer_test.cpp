/**
 * @file lexer_test.cpp
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief A lexer.h tesztelése
 * @version 0.1
 * @date 2022-03-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "gtest_lite.h"
#include "lexer.h"
#include <sstream>

void testLexer(){
    TEST(Lexer, BasicRead){
        std::ifstream in("tests/basicLexer.fl");
        EXPECT_TRUE(in.is_open());
        Lexer l(in);
        EXPECT_NO_THROW(l());

        std::stringstream ss;

        ss << l;

        EXPECT_STREQ("async#module#Foo#(#)#{#a#=#b#&#c#;#a#=#b#&#c#;#}#", ss.str().c_str());

    } END

    TEST(Lexer, EmptyLine){
        std::stringstream in("async\n\n\t\nfoo");
        std::stringstream out;

        Lexer l(in);
        EXPECT_NO_THROW(l());

        out << l;

        EXPECT_STREQ("async#foo#", out.str().c_str());
    }END;

    TEST(Lexer, ModuleWireing){
        std::stringstream in("Foo(clk clk, s1, s2, o);");
        std::stringstream out;

        Lexer l(in);
        EXPECT_NO_THROW(l());

        out << l;

        EXPECT_STREQ("Foo#(#clk#clk#,#s1#,#s2#,#o#)#;#", out.str().c_str());
    }END;
}

int main(){
    testLexer();
    return 0;
}
