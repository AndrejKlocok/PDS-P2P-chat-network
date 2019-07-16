//
// Created by H365379 on 7/15/2019.
//
#include "../src/common/Bencoder.h"
#include "gtest/gtest.h"

class BencoderTest  : public ::testing::Test{

protected:
    Bencoder* benc;

    virtual void TearDown() {
    }

    virtual void SetUp() {
        benc = new Bencoder();
    }
};

TEST_F(BencoderTest, decodeTest1){
    json test = benc->decode("d3:bar4:spam3:fooi42ee");
    json o = json::parse("{\"bar\": \"spam\", \"foo\": 42}");
    EXPECT_EQ(o, test);
}

TEST_F(BencoderTest, encodeTest1){
    std::string test = benc->encode(json::parse("{\"bar\": \"spam\", \"foo\": 42}"));
    std::string o =("d3:bar4:spam3:fooi42ee");
    EXPECT_EQ(o, test);
}