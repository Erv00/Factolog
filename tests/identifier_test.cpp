#include "gtest_lite.h"
#include "identifier.h"
#include "exceptions.h"

#include <sstream>

using namespace factolog;

void identifier_test(){
    TEST(Identifier, ValidTest){
        std::stringstream in("foo");
        Lexer l(in);
        l();

        Identifier *i;
        EXPECT_NO_THROW(i = Identifier::parse(l));

        delete i;

    }END;
    
    TEST(Identifier, ValidTest2){
        std::stringstream in("_f_o_o");
        Lexer l(in);
        l();

        Identifier *i;
        EXPECT_NO_THROW(i = Identifier::parse(l));

        delete i;
    }END;
    
    TEST(Identifier, InvalidTest){
        std::stringstream in("2foo");
        Lexer l(in);
        l();

        EXPECT_THROW(Identifier::parse(l), UnexpectedSymbolError&);
    }END;
}
