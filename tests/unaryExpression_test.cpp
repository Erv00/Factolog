#include "gtest_lite.h"

#include <sstream>

#include "exceptions.h"
#include "unaryExpression.h"

using namespace factolog;

void unaryExpression_test(){
    TEST(UnaryExpression, NormalConst){
        std::stringstream ss("5");
        Lexer l(ss);
        l();

        ValueExpression *v;
        EXPECT_NO_THROW(v = UnaryExpression::parse(l));

        UnaryExpression *unop;
        EXPECT_NO_THROW(unop = dynamic_cast<UnaryExpression*>(v));
        EXPECT_TRUE(unop == NULL);

        EXPECT_TRUE(ss.eof());

        delete v;
    }END;

    TEST(UnaryExpression, PlusConst){
        std::stringstream ss("+5");
        Lexer l(ss);
        l();

        ValueExpression *v;
        EXPECT_NO_THROW(v = UnaryExpression::parse(l));

        UnaryExpression *unop;
        EXPECT_NO_THROW(unop = dynamic_cast<UnaryExpression*>(v));
        //EXPECT_EQ((UnaryExpression*)NULL, unop);
        EXPECT_TRUE(unop == NULL);

        EXPECT_TRUE(ss.eof());

        delete v;
    }END;
    
    TEST(UnaryExpression, MinusConst){
        std::stringstream ss("-5");
        Lexer l(ss);
        l();

        UnaryExpression *unop;
        EXPECT_NO_THROW(unop = dynamic_cast<UnaryExpression*>(UnaryExpression::parse(l)));

        EXPECT_EQ(UnaryExpression::MINUS, unop->op);
        EXPECT_TRUE(ss.eof());

        delete unop;
    }END;

    TEST(UnaryExpression, NotConst){
        std::stringstream ss("~5");
        Lexer l(ss);
        l();

        UnaryExpression *unop;
        EXPECT_NO_THROW(unop = dynamic_cast<UnaryExpression*>(UnaryExpression::parse(l)));

        EXPECT_EQ(UnaryExpression::NOT, unop->op);
        EXPECT_TRUE(ss.eof());

        delete unop;
    }END;
    
    TEST(UnaryExpression, InvalidConst){
        std::stringstream ss("$5");
        Lexer l(ss);
        l();

        EXPECT_THROW(UnaryExpression::parse(l), UnexpectedSymbolError&);
    }END;

    TEST(UnaryExpression, NormalIdentifier){
        std::stringstream ss("foo");
        Lexer l(ss);
        l();

        ValueExpression *v;
        EXPECT_NO_THROW(v = UnaryExpression::parse(l));

        UnaryExpression *unop;
        EXPECT_NO_THROW(unop = dynamic_cast<UnaryExpression*>(v));
        EXPECT_TRUE(unop == NULL);

        EXPECT_TRUE(ss.eof());

        delete v;
    }END;

    TEST(UnaryExpression, PlusIdentifier){
        std::stringstream ss("+foo");
        Lexer l(ss);
        l();

        ValueExpression *v;
        EXPECT_NO_THROW(v = UnaryExpression::parse(l));

        UnaryExpression *unop;
        EXPECT_NO_THROW(unop = dynamic_cast<UnaryExpression*>(v));
        EXPECT_TRUE(unop == NULL);

        EXPECT_TRUE(ss.eof());
        delete v;
    }END;
    
    TEST(UnaryExpression, MinusIdentifier){
        std::stringstream ss("-foo");
        Lexer l(ss);
        l();

        UnaryExpression *unop;
        EXPECT_NO_THROW(unop = dynamic_cast<UnaryExpression*>(UnaryExpression::parse(l)));

        EXPECT_EQ(UnaryExpression::MINUS, unop->op);
        EXPECT_TRUE(ss.eof());

        delete unop;
    }END;

    TEST(UnaryExpression, NotIdentifier){
        std::stringstream ss("~foo");
        Lexer l(ss);
        l();

        UnaryExpression *unop;
        EXPECT_NO_THROW(unop = dynamic_cast<UnaryExpression*>(UnaryExpression::parse(l)));

        EXPECT_EQ(UnaryExpression::NOT, unop->op);
        EXPECT_TRUE(ss.eof());

        delete unop;
    }END;
    
    TEST(UnaryExpression, InvalidIdentifier){
        std::stringstream ss("$foo");
        Lexer l(ss);
        l();

        EXPECT_THROW(UnaryExpression::parse(l), UnexpectedSymbolError&);
    }END;

    //( expression )
    TEST(UnaryExpression, Normal(expression)){
        std::stringstream ss("(5)");
        Lexer l(ss);
        l();

        ValueExpression *v;
        EXPECT_NO_THROW(v = UnaryExpression::parse(l));

        UnaryExpression *unop;
        EXPECT_NO_THROW(unop = dynamic_cast<UnaryExpression*>(v));
        EXPECT_TRUE(unop == NULL);

        EXPECT_TRUE(ss.eof());
        delete v;
    }END;
    //( expression )
    TEST(UnaryExpression, not(expression)){
        std::stringstream ss("~(5)");
        Lexer l(ss);
        l();

        ValueExpression *v;
        EXPECT_NO_THROW(v = UnaryExpression::parse(l));

        UnaryExpression *unop;
        EXPECT_NO_THROW(unop = dynamic_cast<UnaryExpression*>(v));
        EXPECT_TRUE(unop != NULL);

        EXPECT_EQ(UnaryExpression::NOT, unop->op);

        EXPECT_TRUE(ss.eof());

        delete unop;
    }END;
}
