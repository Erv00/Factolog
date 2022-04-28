#include <gtest_lite.h>
#include <memtrace.h>

#include "variableDeclaration.h"
#include "lexer.h"

#include <sstream>

using namespace factolog;

void variableDeclaration_test() {
    TEST(VariableDeclaration, single){
        std::stringstream ss("var foo;");
        Lexer lex(ss);
        lex();

        VariableDeclaration *vardecl = VariableDeclaration::parse(lex);
        EXPECT_EQ((size_t)1, vardecl->getDeclaredVariables().size());
        EXPECT_STREQ("foo", vardecl->getDeclaredVariables()[0]->getName().c_str());
        delete vardecl;
    }END;

    TEST(VariableDeclaration, single){
        std::stringstream ss("var foo, bar;");
        Lexer lex(ss);
        lex();

        VariableDeclaration *vardecl = VariableDeclaration::parse(lex);
        EXPECT_EQ((size_t)2, vardecl->getDeclaredVariables().size());
        EXPECT_STREQ("foo", vardecl->getDeclaredVariables()[0]->getName().c_str());
        EXPECT_STREQ("bar", vardecl->getDeclaredVariables()[1]->getName().c_str());
        delete vardecl;
    }END;
    
}
