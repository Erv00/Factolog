#include "gtest_lite.h"

#include <sstream>

#include "value.h"
#include "exceptions.h"

using namespace factolog;

void value_test(){
    TEST(Value, ValidTest){
        std::stringstream in("foo");
        Lexer l(in);
        l();

        Value *i;
        EXPECT_NO_THROW(i = Value::parse(l));

        delete i;

    }END;
    
    TEST(Value, ValidTest2){
        std::stringstream in("_f_o_o");
        Lexer l(in);
        l();

        Value *i;
        EXPECT_NO_THROW(i = Value::parse(l));

        delete i;
    }END;
    
    TEST(Value, InvalidTest){
        std::stringstream in("2foo");
        Lexer l(in);
        l();

        EXPECT_THROW(Value::parse(l), UnexpectedSymbolError&);
    }END;

    TEST(Value, ValidTest3){
        std::stringstream in("69");
        Lexer l(in);
        l();

        Value *i;
        EXPECT_NO_THROW(i = Value::parse(l));

        delete i;

    }END;
    
    TEST(Value, ValidTest4){
        std::stringstream in("421");
        Lexer l(in);
        l();

        Value *i;
        EXPECT_NO_THROW(i = Value::parse(l));

        delete i;
    }END;
    
    TEST(Value, Valid5){
        std::stringstream in("foo");
        Lexer l(in);
        l();

        Value* val;
        EXPECT_NO_THROW(val = Value::parse(l));
        delete val;
    }END;
    
    TEST(Value, Overflow){
        std::stringstream in("214748364700");   //This number is too large
        Lexer l(in);
        l();

        EXPECT_THROW(Value::parse(l), UnableToRepresentError&);
    }END;
}
