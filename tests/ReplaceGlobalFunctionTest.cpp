/*
 * ReplaceGlobalFunctionTest.cpp
 *
 * Created on: Tue Dec 20 2022
 *     Author: Tin Tran <realtrantrungtin@gmail.com>
 */

#include <dobby.h>
#include <gtest/gtest.h>
#include "Dummy.h"
#include "gmocke-hook-helper.h"
#include "logging/logging.h"

using namespace googlemock_extension::helper;

#define RESOLVE(name) DobbySymbolResolver(NULL, #name)

TEST(ReplaceGlobalFuntionTest, BeforeReplace) {
  EXPECT_EQ(4, global_func_return_4());
  EXPECT_EQ(5, global_func_return_5());
}

int global_func_return_4_overload() {
  return 4;
}

int global_func_return_4_overload(int arg1) {
  return arg1;
}

double global_func_return_4_overload(double arg1) {
  return arg1;
}

double global_func_return_4_overload(int arg1, double arg2) {
  return arg2;
}

struct SettingLifecycle {
  SettingLifecycle() { dobby_enable_near_branch_trampoline(); }
  ~SettingLifecycle() { dobby_disable_near_branch_trampoline(); }
};

TEST(ReplaceGlobalFuntionTest, Replace) {
  SettingLifecycle settings;
  replace_func_t(global_func_return_4, global_func_return_5);
  EXPECT_EQ(5, global_func_return_4());
  restore_func_t(global_func_return_4);
  EXPECT_EQ(4, global_func_return_4());
}

TEST(ReplaceGlobalFuntionTest, ReplaceOverload_TC1) {
  SettingLifecycle settings;
  int (*global_func_return_4_overload_ptr)();
  global_func_return_4_overload_ptr = global_func_return_4_overload;
  replace_func_t(global_func_return_4_overload_ptr, global_func_return_5);
  EXPECT_EQ(5, global_func_return_4_overload());
  restore_func_t(global_func_return_4_overload_ptr);
  EXPECT_EQ(4, global_func_return_4_overload());
}

TEST(ReplaceGlobalFuntionTest, ReplaceOverload_TC2) {
  SettingLifecycle settings;
  int (*global_func_return_4_overload_arg1_ptr)(int);
  global_func_return_4_overload_arg1_ptr = global_func_return_4_overload;
  replace_func_t(global_func_return_4_overload_arg1_ptr, global_func_return_5);
  EXPECT_EQ(5, global_func_return_4_overload(10));
  restore_func_t(global_func_return_4_overload_arg1_ptr);
  EXPECT_EQ(4, global_func_return_4_overload());
}

TEST(ReplaceGlobalFuntionTest, ReplaceOverload_TC3) {
  SettingLifecycle settings;
  double (*global_func_return_4_overload_arg1_ptr)(double);
  global_func_return_4_overload_arg1_ptr = global_func_return_4_overload;
  replace_func_t(global_func_return_4_overload_arg1_ptr,
                 global_func_return_5_0);
  EXPECT_EQ(5, global_func_return_4_overload(10.0));
  restore_func_t(global_func_return_4_overload_arg1_ptr);
  EXPECT_EQ(4, global_func_return_4_overload());
}

TEST(ReplaceGlobalFuntionTest, ReplaceOverload_TC4) {
  SettingLifecycle settings;
  double (*global_func_return_4_overload_2args_ptr)(int, double);
  global_func_return_4_overload_2args_ptr = global_func_return_4_overload;
  replace_func_t(global_func_return_4_overload_2args_ptr,
                 global_func_return_5_0);
  EXPECT_EQ(5, global_func_return_4_overload(3, 10.0));
  restore_func_t(global_func_return_4_overload_2args_ptr);
  EXPECT_EQ(10.0, global_func_return_4_overload(3, 10.0));
}

TEST(ReplaceGlobalFuntionTest, ReplacesStatic) {
  SettingLifecycle settings;
  replace_func_t(static_global_func_return_6, global_func_return_5);
  EXPECT_EQ(5, static_global_func_return_6());
  restore_func_t(static_global_func_return_6);
  EXPECT_EQ(6, static_global_func_return_6());
}

TEST(ReplaceGlobalFuntionTest, ReplacesInline) {
  SettingLifecycle settings;
  replace_func_t(inline_global_func_return_7, global_func_return_5);
  EXPECT_EQ(5, inline_global_func_return_7());
  restore_func_t(inline_global_func_return_7);
  EXPECT_EQ(7, inline_global_func_return_7());
}

TEST(ReplaceGlobalFuntionTest, ReplacesStaticInline) {
  SettingLifecycle settings;
  replace_func_t(static_inline_global_func_return_8, global_func_return_5);
  EXPECT_EQ(5, static_inline_global_func_return_8());
  restore_func_t(static_inline_global_func_return_8);
  EXPECT_EQ(8, static_inline_global_func_return_8());
}

TEST(ReplaceGlobalFuntionTest, ReplacesTemplate) {
  SettingLifecycle settings;
  replace_func_t(template_add<int>, global_func_return_5);
  EXPECT_EQ(5, template_add(1, 2));
  restore_func_t(template_add<int>);
  EXPECT_EQ(3, template_add(1, 2));
}