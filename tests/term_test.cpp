#include <gtest_lite.h>
#include <memtrace.h>

#include "term.h"
#include "lexer.h"
#include <sstream>

using namespace factolog;

void term_test() {
    TEST(Term, Constness){
        std::stringstream ss("6/3");

        Lexer lex(ss);
        lex();

        ValueExpression *exp = Term::parse(lex);
        EXPECT_TRUE(exp->isConst());
        EXPECT_EQ(2, exp->calculate());
        delete exp;
    }END;
}
