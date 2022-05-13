#include <gtest_lite.h>

#include "memtrace.h"
#include <vector>
#include <string>
#include <sstream>
#include "argumentParser.h"

char** cstrToArgs(const char * const *args, size_t num){
    char **ret = new char*[num+1];
    for(size_t i = 0; args[i] != NULL; i++){
        ret[i] = new char[strlen(args[i])+1];
        strcpy(ret[i], args[i]);
    }
    ret[num] = NULL;
    return ret;
}

void delargs(char **args){
    for(size_t i=0; args[i] != NULL; i++)
        delete[] args[i];
    delete[] args;
    /*delete[] *args;
    delete[] args;
*/
}

void argumentParser_test(){
//Due to a mismatch in the way the C function getopts_long expects
//its arguments, it cannot be tested without some warnings, or a lot of
//otherwise unnecessary code
#ifndef CPORTA
    TEST(ArgumentParser, NoArguments){
        int argc = 1;
        const char *toConv[] = {"./factoTest", NULL};
        char **argv = cstrToArgs(toConv, 1);

        EXPECT_THROW(Configuration c(argc, argv),char const*);
        delargs(argv);
    }END;

    TEST(ArgumentParser, Help){
        int argc = 2;
        const char *toConv[] = {"./factoTest", "-h", NULL};
        char **argv = cstrToArgs(toConv, 2);

        EXPECT_THROW(Configuration c(argc, argv), const char*);
        delargs(argv);
    }END;

    TEST(argumentParser, STDIN){
        int argc = 2;
        const char *toConv[] = {"./factoTest", "-", NULL};
        char **argv = cstrToArgs(toConv, 2);

        Configuration *c;
        EXPECT_NO_THROW(c = new Configuration (argc, argv));

        EXPECT_STREQ("-", c->getInputFile().c_str());
        EXPECT_TRUE(c->printBlueprint());
        EXPECT_FALSE(c->printDot());
        
        std::vector<std::string> signals = c->getSignals();
        EXPECT_EQ((size_t)0, signals.size());
        delete c;
        delargs(argv);
    }END;

    TEST(argumentParser, Signals){
        int argc = 4;
        const char *toConv[] = {"./factoTest", "-s", "sig0, sig1, sig2", "-", NULL};
        char **argv = cstrToArgs(toConv, 4);

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
        delargs(argv);
    }END;
#endif
}

