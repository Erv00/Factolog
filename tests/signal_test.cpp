#include "signals.h"

#include "gtest_lite.h"
#include <sstream>

using namespace factolog;

void signal_test(){
    TEST(Signal, Out){
        unsigned int sig = 1;
        bool isConst = false;

        Signal<1> s(sig, isConst, true);

        std::stringstream ss;
        ss << s;
        EXPECT_STREQ("\"output_signal\":{\"type\":\"virtual\",\"name\":\"signal-A\"}", ss.str().c_str());
    }END;
    TEST(Signal, OneIn){
        unsigned int sig = 1;
        bool isConst = false;

        Signal<1> s(sig, isConst);

        std::stringstream ss;
        ss << s;
        EXPECT_STREQ("\"first_signal\":{\"type\":\"virtual\",\"name\":\"signal-A\"}", ss.str().c_str());
    }END;
    TEST(Signal, TwoIn){
        Color sig[] = {1,2};
        bool isConst[] = {false, false};

        Signal<2> s(sig, isConst);

        std::stringstream ss;
        ss << s;
        EXPECT_STREQ(
            "\"first_signal\":{\"type\":\"virtual\",\"name\":\"signal-A\"},"
            "\"second_signal\":{\"type\":\"virtual\",\"name\":\"signal-B\"}",
            ss.str().c_str());
    }END;

    TEST(Signal, ConstIn){
        unsigned int sig = 420;
        bool isConst = true;

        Signal<1> s(sig, isConst);

        std::stringstream ss;
        ss << s;
        EXPECT_STREQ("\"first_constant\":420", ss.str().c_str());
    }END;
}
