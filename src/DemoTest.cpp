#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "MockDemo.h"

#define private public
#define protected public

using namespace testing;
using ::testing::_;

class DemoTest : public testing::Test {
  void SetUp() override { mMock = std::make_shared<MockDemo>(); }

  void TearDown() override {}

 private:
  std::shared_ptr<MockDemo> mMock;
};

TEST_F(DemoTest, TestSub) {
  EXPECT_CALL(*mMock, sub(_, _)).WillOnce([] { return 10; });
  EXPECT_EQ(10, mMock->sub(2, 3));
}

TEST_F(DemoTest, TestAdd) {
  EXPECT_CALL_EX(*mMock, add(_, _)).WillOnce([] { return 10; });
  EXPECT_EQ(10, mMock->add(2, 3));
}

TEST_F(DemoTest, TestAdd2) {
  ON_CALL_EX(*mMock, add).WillByDefault([] { return 16; });
  EXPECT_EQ(16, mMock->add(2, 3));
}

TEST_F(DemoTest, TestAdd3) { EXPECT_EQ(5, mMock->add(2, 3)); }

TEST_F(DemoTest, TestMul) {
  EXPECT_CALL_EX(*mMock, mul(_, _, _)).WillOnce([] { return 100; });
  EXPECT_EQ(100, mMock->mul(2, 3, 4));
}

TEST_F(DemoTest, TestMul2) {
  ON_CALL_EX(*mMock, mul).WillByDefault([] { return 106; });
  EXPECT_EQ(106, mMock->mul(2, 3, 4));
}

TEST_F(DemoTest, TestMul3) { EXPECT_EQ(24, mMock->mul(2, 3, 4)); }
