#include <gtest_lite.h>

#include <sstream>
#include <iostream>

#include "lexer.h"
#include "expression.h"
#include "modules.h"

using namespace factolog;

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

        delete val;
    }END;

    TEST(Dot, Complex){
        std::stringstream ss("async module Foo(out baz){"
                "var a, b;"
                "Bar(a, a&b, 5);"
                "a = 6+9;"
                "}");
        Lexer l(ss);
        EXPECT_NO_THROW(l());

        AsyncModule *am;
        EXPECT_NO_THROW(am = AsyncModule::parse(l));

        EXPECT_TRUE(am != NULL);

        std::cout << "digraph G{\n";

        am->printDot(std::cout) << "}\n";

        delete am;
    }END;

    TEST(Dot, 41Mul File){
        std::ifstream in("tests/4_1mul.fl");
        EXPECT_TRUE(in.is_open());
        Lexer l(in);
        EXPECT_NO_THROW(l());

        AsyncModule *am;
        EXPECT_NO_THROW(am = AsyncModule::parse(l));

        std::cout << "digraph G{\n";

        am->printDot(std::cout) << "}\n";

        delete am;
    }END;
}
