#include <gtest_lite.h>

#include "assignment.h"
#include "number.h"

#include <sstream>

using namespace factolog;

void assignment_test(){
    TEST(Assignment, ValidIdentifier){
        std::stringstream in("foo=5;");
        Lexer l(in);
        l();

        Assignment *a;
        EXPECT_NO_THROW(a = Assignment::parse(l));

        EXPECT_STREQ("foo", a->getIdentifier()->getName().c_str());
        
        Number *n = dynamic_cast<Number*>(a->getValue());
        
        ASSERT_EQ(true, n != NULL);

        EXPECT_EQ(5, n->calculate());

        EXPECT_TRUE(l.eof());

        delete a;
    }END;
}
