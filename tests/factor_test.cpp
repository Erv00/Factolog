#include <gtest_lite.h>
#include <memtrace.h>

#include "factor.h"
#include "lexer.h"
#include <sstream>

using namespace factolog;

void factor_test() {
    TEST(Factor, Constness){
        std::stringstream ss("2**2**3");

        Lexer lex(ss);
        lex();

        ValueExpression *exp = Factor::parse(lex);
        EXPECT_TRUE(exp->isConst());
        EXPECT_EQ(256, exp->calculate());
        delete exp;
    }END;
}
