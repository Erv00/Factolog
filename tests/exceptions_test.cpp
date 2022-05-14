#include "gtest_lite.h"

#include "exceptions.h"

#include <sstream>
#include "lexer.h"
#include "value.h"
#include "modules.h"
#include "compiler.h"

#include "memtrace.h"

using namespace factolog;

void exceptions_test(){
    TEST(Exceptions, TokenExpectedError){
        std::stringstream ss("a b c");
        Lexer l(ss);
        EXPECT_NO_THROW(l());
        EXPECT_THROW(l.except("x"), TokenExpectedError&);
    }END;

    TEST(Exceptions, UnableToRepresentError){
        std::stringstream ss("2147483648");
        Lexer l(ss);
        EXPECT_NO_THROW(l());
        EXPECT_THROW(Value::parse(l), UnableToRepresentError&);
    }END;

    TEST(Exceptions, UnexpectedSympolError){
        std::stringstream ss("$foo");
        Lexer l(ss);
        EXPECT_NO_THROW(l());

        EXPECT_THROW(Identifier::parse(l), UnexpectedSymbolError&);
    }END;

    TEST(Exceptions, EmptyParameterListError){
        std::stringstream ss("async module foo() {}");
        Lexer l(ss);
        EXPECT_NO_THROW(l());

        EXPECT_THROW(AsyncModule::parse(l), EmptyParameterListError&);
    }END;

    TEST(Exceptions, MismatchedParametersError){
        std::stringstream ss("async module foo(in a, in b){} async module main(in a){foo(a);}");
        std::stringstream out;
        Compiler c(ss,out);
        c.printBlueprintFlag() = false;
        c.printDotFlag() = true;

        EXPECT_THROW(c.compile(), MismatchedParametersError&);
    }END;

    TEST(Exceptions, ModuleAlreadyDefinedError){
        std::stringstream ss("async module foo(in a){} async module foo(in a){}");
        std::stringstream out;
        Compiler c(ss,out);
        c.printBlueprintFlag() = false;
        c.printDotFlag() = true;

        EXPECT_THROW(c.compile(), ModuleAlreadyDefinedError&);
    }END;

    TEST(Exceptions, ModuleNotDefinedError){
        std::stringstream ss("async module main(in a){foo(a);}");
        std::stringstream out;
        Compiler c(ss,out);
        c.printBlueprintFlag() = false;
        c.printDotFlag() = true;

        EXPECT_THROW(c.compile(), ModuleNotDefinedError&);
    }END;

    TEST(Exceptions, UndefinedVariableError){
        std::stringstream ss("async module main(out a){a=b+2;}");
        std::stringstream out;
        Compiler c(ss,out);
        c.printBlueprintFlag() = false;
        c.printDotFlag() = true;

        EXPECT_THROW(c.compile(), UndefinedVariableError&);
    }END;

    TEST(Exceptions, VariableAlreadyDefinedError){
        std::stringstream ss("async module main(out a){var a;}");
        std::stringstream out;
        Compiler c(ss,out);
        c.printBlueprintFlag() = false;
        c.printDotFlag() = true;

        EXPECT_THROW(c.compile(), VariableAlreadyDefinedError&);
    }END;

    TEST(Exceptions, VariableReassignmentError){
        std::stringstream ss("async module main(out a){a=3+2;a=6;}");
        std::stringstream out;
        Compiler c(ss,out);
        c.printBlueprintFlag() = false;
        c.printDotFlag() = true;

        EXPECT_THROW(c.compile(), VariableReassignmentError&);
    }END;
}

