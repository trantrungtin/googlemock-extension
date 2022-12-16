#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "MockDemo.h"
#include "set_function_jump.h"

#include <memory>

#define private public
#define protected public

using namespace testing;
using ::testing::_;

class DemoTest : public testing::Test {
    void SetUp() override {
        mMock = std::make_shared<MockDemo>();
    }

    void TearDown() override {
    }

private:
    std::shared_ptr<MockDemo> mMock;
};

TEST_F(DemoTest, TestSub) {
    EXPECT_CALL(*mMock, sub(_, _)).WillOnce([] { return 10; });
    EXPECT_EQ(10, mMock->sub(2, 3));
}

TEST_F(DemoTest, TestAdd) {
    mMock->test();
    GmockExLifecycle life = mMock->GMOCK_EX_SETUP_add(_, _);
    EXPECT_CALL(*mMock, GMOCK_EX_add(_,_))
        .WillOnce([] { return 10; });
    EXPECT_EQ(11, mMock->add(2, 3));
}
