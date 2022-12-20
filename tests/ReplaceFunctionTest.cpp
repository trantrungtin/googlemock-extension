/*
 * ReplaceFunctionTest.cpp
 *
 * Created on: Sun Dec 18 2022
 *     Author: Tin Tran <realtrantrungtin@gmail.com>
 */

#include <dobby.h>
#include <gtest/gtest.h>
#include "gmocke-hook-helper.h"
#include "logging/logging.h"
#include "Dummy.h"

using namespace googlemock_extension::helper;

class DemoReplace {
 public:
  int func_return_1() { return 1; }

  int func_return_2() { return 2; }

  static int static_func_return_3() { return 3; }
};

TEST(ReplaceFuntionTest, BeforeReplace) {
  DemoReplace obj;
  EXPECT_EQ(1, obj.func_return_1());
  EXPECT_EQ(2, obj.func_return_2());
  EXPECT_EQ(3, obj.static_func_return_3());
  EXPECT_EQ(3, DemoReplace::static_func_return_3());
}

TEST(ReplaceFuntionTest, Replace) {
  DemoReplace obj;
  replace_func_t(&DemoReplace::func_return_1, &DemoReplace::func_return_2);
  EXPECT_EQ(2, obj.func_return_1());
  restore_func_t(&DemoReplace::func_return_1);
  EXPECT_EQ(1, obj.func_return_1());
}

TEST(ReplaceFuntionTest, ReplaceStatic) {
  DemoReplace obj;
  replace_func_t(&DemoReplace::static_func_return_3,
                 &DemoReplace::func_return_2);
  EXPECT_EQ(2, obj.static_func_return_3());
  EXPECT_EQ(2, DemoReplace::static_func_return_3());
  restore_func_t(&DemoReplace::static_func_return_3);
  EXPECT_EQ(3, obj.static_func_return_3());
  EXPECT_EQ(3, DemoReplace::static_func_return_3());
}