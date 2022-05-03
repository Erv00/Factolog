#include <gtest_lite.h>

#include <sstream>
#include "base64.h"

void base64_test(){
    TEST(Base64, Basic){
        Base64 b64;

        b64.encode("Many hands make light work.");

        std::stringstream ss;
        ss << b64;

        EXPECT_STREQ("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu", ss.str().c_str());
    }END;

    TEST(Base64, PaddingOne){
        Base64 b64;

        b64.encode("Ma");

        std::stringstream ss;
        ss << b64;

        EXPECT_STREQ("TWE=", ss.str().c_str());
    }END;

    TEST(Base64, Padding2){
        Base64 b64;

        b64.encode("Prog");

        std::stringstream ss;
        ss << b64;

        EXPECT_STREQ("UHJvZw==", ss.str().c_str());
    }END;

    TEST(Base64, Clearing){
        Base64 b64;

        b64.encode("asdasd");

        std::stringstream ss;
        ss << b64;

        EXPECT_EQ((size_t)0, b64.getBuf().size());
    }END;
}
