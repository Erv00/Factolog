#include <gtest_lite.h>

#include <sstream>
#include <iostream>

#include "lexer.h"
#include "lexemes.h"

void dot_test(){
    TEST(Dot, Basic){
        std::stringstream ss("-b+(b**2-4*a*c)**(1/2)");
        Lexer l(ss);
        EXPECT_NO_THROW(l());

        ValueExpression *val;
        EXPECT_NO_THROW(val = Expression::parse(l));

        std::stringstream out;
        EXPECT_NO_THROW(val->printDot(out));

        std::cout << out.str();
    }END;
}
