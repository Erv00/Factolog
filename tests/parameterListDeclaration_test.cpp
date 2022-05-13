#include "gtest_lite.h"

#include "parameters.h"
#include "lexer.h"
#include "exceptions.h"
#include <sstream>
#include <string>

void parameterListDeclaration_test(){
    TEST(ParameterListDeclaration, Basic){
        std::stringstream ss("in a, in b, out c");
        Lexer l(ss);
        l();
        
        ParameterListDeclaration *pl = ParameterListDeclaration::parse(l);
    
        EXPECT_EQ(2, pl->getNumInputs());
        EXPECT_EQ(1, pl->getNumOutputs());
        delete pl;
    }END;

    TEST(ParameterListDeclaration, NoConnection){
        std::stringstream ss(" ");
        Lexer l(ss);
        l();

        EXPECT_THROW(ParameterListDeclaration::parse(l), EmptyParameterListError&);
    }END;
}
