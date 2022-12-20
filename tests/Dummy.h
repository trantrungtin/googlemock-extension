/*
 * Dummy.h
 *
 * Created on: Tue Dec 20 2022
 *     Author: Tin Tran <realtrantrungtin@gmail.com>
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int global_func_return_4();
int global_func_return_5();
double global_func_return_5_0();

static int static_global_func_return_6() {
  return 6;
}

inline int inline_global_func_return_7() {
  return 7;
}

static inline int static_inline_global_func_return_8() {
  return 8;
}

#ifdef __cplusplus
}

#endif

template <typename T1>
T1 template_add(T1 a, T1 b) {
  return a + b;
}

