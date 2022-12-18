/*
 * gmock-jump-helper.h
 *
 * Created on: Sun Dec 18 2022
 *     Author: Tin Tran <realtrantrungtin@gmail.com>
 */

#pragma once

#include <unistd.h>

#include <cstddef>
#include <vector>

namespace googlemock_extension {
namespace helper {

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*gmocke_dummy_func_t)();

int replace_func(void* origin, void* replace);

int restore_func(void* origin);

#ifdef __cplusplus
}
#endif

template <typename F1, typename F2>
int replace_func_t(F1 origin, F2 replace) {
  void* origin_ = reinterpret_cast<void*>((size_t&)origin);
  void* replace_ = reinterpret_cast<void*>((size_t&)replace);
  return replace_func(origin_, replace_);
}

template <typename F1>
int restore_func_t(F1 origin) {
  void* origin_ = reinterpret_cast<void*>((std::size_t&)origin);
  return restore_func(origin_);
}

}  // namespace helper
}  // namespace googlemock_extension

#define GMOCK_EX_REPLACE_FUNC(F1, F2) \
  googlemock_extension::helper::replace_func_t(F1, F2)

#define GMOCK_EX_RESTORE_FUNC(F1) \
  googlemock_extension::helper::restore_func_t(F1)
