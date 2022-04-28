#include <gtest_lite.h>
#include <memtrace.h>

#include "expression.h"
#include "lexer.h"

#include <sstream>

using namespace factolog;

void expression_test() {
    TEST(Expression, Constness){
        std::stringstream ss("5+8-4");

        Lexer lex(ss);
        lex();

        ValueExpression *exp = Expression::parse(lex);
        EXPECT_TRUE(exp->isConst());
        EXPECT_EQ(9, exp->calculate());
        delete exp;
    }END;
}
