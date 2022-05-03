#include <gtest_lite.h>

#include <vector>
#include <string>
#include <sstream>
#include "argumentParser.h"

void argumentParser_test(){
//Due to a mismatch in the way the C function getopts_long expects
//its arguments, it cannot be tested without some warnings, or a lot of
//otherwise unnecessary code
#ifndef CPRORTA
    TEST(ArgumentParser, NoArguments){
        int argc = 1;
        char *argv[] = {"./factoTest", NULL};

        EXPECT_THROW(Configuration c(argc, argv),char const*);
    }END;

    TEST(ArgumentParser, Help){
        int argc = 2;
        char *argv[] = {"./factoTest", "-h", NULL};

        EXPECT_THROW(Configuration c(argc, argv), const char*);
    }END;

    TEST(argumentParser, STDIN){
        int argc = 2;
        char *argv[] = {"./factoTest", "-", NULL};

        Configuration *c;
        EXPECT_NO_THROW(c = new Configuration (argc, argv));

        EXPECT_STREQ("-", c->getInputFile().c_str());
        EXPECT_TRUE(c->printBlueprint());
        EXPECT_FALSE(c->printDot());
        
        std::vector<std::string> signals = c->getSignals();
        EXPECT_EQ((size_t)0, signals.size());
        delete c;
    }END;

    TEST(argumentParser, Signals){
        int argc = 4;
        char *argv[] = {"./factoTest", "-s", "sig0, sig1, sig2", "-", NULL};

        Configuration *c;
        EXPECT_NO_THROW(c = new Configuration (argc, argv));

        EXPECT_STREQ("-", c->getInputFile().c_str());
        EXPECT_TRUE(c->printBlueprint());
        EXPECT_FALSE(c->printDot());
        
        std::vector<std::string> signals = c->getSignals();
        EXPECT_EQ((size_t)3, signals.size());
        EXPECT_STREQ("sig0", signals[0].c_str());
        EXPECT_STREQ("sig1", signals[1].c_str());
        EXPECT_STREQ("sig2", signals[2].c_str());
        delete c;
    }END;
#endif
}
