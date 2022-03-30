#include <gtest_lite.h>

#include <sstream>

#include "exceptions.h"
#include "number.h"

void number_test(){
    TEST(Number, ValidTest){
        std::stringstream in("69");
        Lexer l(in);
        l();

        Number *i;
        EXPECT_NO_THROW(i = Number::parse(l));

        delete i;

    }END;
    
    TEST(Number, ValidTest2){
        std::stringstream in("421");
        Lexer l(in);
        l();

        Number *i;
        EXPECT_NO_THROW(i = Number::parse(l));

        delete i;
    }END;
    
    TEST(Number, Invalid){
        std::stringstream in("foo");
        Lexer l(in);
        l();

        EXPECT_THROW(Number::parse(l), UnexpectedSymbolError&);
    }END;
    
    TEST(Number, Overflow){
        std::stringstream in("214748364700");   //This number is too large
        Lexer l(in);
        l();

        EXPECT_THROW(Number::parse(l), UnableToRepresentError&);
    }END;

    TEST(Number, Dot){
        std::stringstream in("69");
        Lexer l(in);
        l();

        Number *i;
        EXPECT_NO_THROW(i = Number::parse(l));

        std::stringstream out;
        EXPECT_NO_THROW(i->printDot(out));

        delete i;
    }END;
}
