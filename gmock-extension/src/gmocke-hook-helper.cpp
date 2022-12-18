/*
 * gmoc-jump-helper.cpp
 *
 * Created on: Sun Dec 18 2022
 *     Author: Tin Tran <realtrantrungtin@gmail.com>
 */

#include "gmocke-hook-helper.h"
#include <dobby.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstddef>
#include <vector>

namespace googlemock_extension {
namespace helper {

template <typename F1, typename F2>
int replace_func(F1 origin, F2 replace, gmocke_dummy_func_t* backup) {
  void* origin_ = reinterpret_cast<void*>((std::size_t&)origin);
  void* replace_ = reinterpret_cast<void*>((std::size_t&)replace);
  return DobbyHook(origin_, (dobby_dummy_func_t)replace_,
                   (dobby_dummy_func_t*)backup);
}

template <typename F1, typename F2>
int replace_func(F1 origin, F2 replace) {
  return replace_func(origin, replace, nullptr);
}

int restore_func(void* origin) {
  return DobbyDestroy(origin);
}

}  // namespace helper
}  // namespace googlemock_extension
