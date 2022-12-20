/*
 * ReplaceFunctionTest.cpp
 *
 * Created on: Sun Dec 18 2022
 *     Author: Tin Tran <realtrantrungtin@gmail.com>
 */

#include <dobby.h>
#include <gtest/gtest.h>
#include "Dummy.h"
#include "gmocke-hook-helper.h"
#include "logging/logging.h"

using namespace googlemock_extension::helper;

class DemoReplace {
 public:
  int func_return_1() { return 1; }

  int func_return_2() { return 2; }

  int func_overload_return_3() { return 3; }

  int func_overload_return_3(int) { return 3; }

  int func_overload_return_3(int, int) { return 3; }

  static int static_func_return_3() { return 3; }
};

template <typename T>
class DemoTemplate {
 public:
  T add(T a, T b) { return a + b; }
};

template <typename T>
class ConcreteTemplate : public DemoTemplate<T> {
 public:
  int fake_mul(int a, int b) { return a * b; }
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

TEST(ReplaceFuntionTest, ReplaceOverload_TC1) {
  DemoReplace obj;
  int (DemoReplace::*func_overload_return_3)();
  func_overload_return_3 = &DemoReplace::func_overload_return_3;
  replace_func_t(func_overload_return_3, &DemoReplace::func_return_2);
  EXPECT_EQ(2, obj.func_overload_return_3());
  restore_func_t(func_overload_return_3);
  EXPECT_EQ(3, obj.func_overload_return_3());
}

TEST(ReplaceFuntionTest, ReplaceOverload_TC2) {
  DemoReplace obj;
  int (DemoReplace::*func_overload_return_3)(int);
  func_overload_return_3 = &DemoReplace::func_overload_return_3;
  replace_func_t(func_overload_return_3, &DemoReplace::func_return_2);
  EXPECT_EQ(2, obj.func_overload_return_3(100));
  restore_func_t(func_overload_return_3);
  EXPECT_EQ(3, obj.func_overload_return_3());
}

TEST(ReplaceFuntionTest, ReplaceOverload_TC3) {
  DemoReplace obj;
  int (DemoReplace::*func_overload_return_3)(int, int);
  func_overload_return_3 = &DemoReplace::func_overload_return_3;
  replace_func_t(func_overload_return_3, &DemoReplace::func_return_2);
  EXPECT_EQ(2, obj.func_overload_return_3(100, 200));
  restore_func_t(func_overload_return_3);
  EXPECT_EQ(3, obj.func_overload_return_3());
}

TEST(ReplaceFuntionTest, ReplaceTemplate) {
  ConcreteTemplate<int> obj;
  replace_func_t(&ConcreteTemplate<int>::add, &ConcreteTemplate<int>::fake_mul);
  EXPECT_EQ(12, obj.add(3, 4));
  restore_func_t(&ConcreteTemplate<int>::add);
  EXPECT_EQ(7, obj.add(3, 4));
}
