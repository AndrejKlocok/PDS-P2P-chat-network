//
// Created by H365379 on 7/16/2019.
//
#include "../src/common/Socket.h"
#include "gtest/gtest.h"

class SocketTest : public ::testing::Test{

protected:
    Socket *socket;

    virtual void TearDown() {
        socket->~Socket();
    }

    virtual void SetUp() {
       socket = new Socket("127.0.0.1", 42069);
    }
};

TEST_F(SocketTest, LocalhostBind){
    socket->bindSocket();
}

TEST_F(SocketTest, SendAndRecvSmallData){
    socket->bindSocket();
    json msg = {
            {"text","Hello world"}
    };
    socket->sendData(msg);
    json recv = socket->recvData();
    EXPECT_EQ(msg, recv);
}
