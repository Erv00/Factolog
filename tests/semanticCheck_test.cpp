#include "gtest_lite.h"

#include "lexer.h"
#include "modules.h"
#include "compilationUnit.h"
#include "identifier.h"
#include <sstream>
#include <map>
#include "memtrace.h"

void semanticCheck_test(){
    TEST(Semantic, Basic){
        std::stringstream ss("async module foo(in i, out o) { o=3*i+i**2 | (i & 1 ^ 2) - ( 2 << 2); }");
        Lexer l(ss);

        EXPECT_NO_THROW(l());
        AsyncModule *mod;
        EXPECT_NO_THROW(mod = AsyncModule::parse(l));

        std::map<const Identifier, Module*> modules;
        modules[*mod->getIdentifier()] = mod;

        CompilationUnit cu(modules);
        EXPECT_NO_THROW(mod->checkSemantics(cu));

        delete mod;
    }END;
}

