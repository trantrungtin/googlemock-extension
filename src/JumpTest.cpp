/*
 * JumpTest.cpp
 *
 * Created on: Sat Dec 17 2022
 *     Author: Tin Tran <realtrantrungtin@gmail.com>
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#define private public
#define protected public

using namespace testing;
using ::testing::_;

class JumpTest : public testing::Test {
  void SetUp() override {}

  void TearDown() override {}

 private:
};

void func1() { printf("func1\n"); }

void func2() { printf("func2\n"); }

TEST_F(JumpTest, TC1) {
#if defined(__arm64__) || defined(__arm__) || defined(__thumb__)
  // #pragma message "ARM here"
  //   printf("Arm here\n");
  void* symbol = reinterpret_cast<void*>((std::size_t&)func1);
  printf("%p\n", reinterpret_cast<uintptr_t>(symbol));
  if ((reinterpret_cast<uintptr_t>(symbol) & 0x1) == 0) {
    printf("arm\n");
  } else {
    printf("thumb\n");
  }
#endif
}
