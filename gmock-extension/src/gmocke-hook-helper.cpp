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

int replace_func(void* origin, void* replace) {
  return DobbyHook(origin, (dobby_dummy_func_t)replace,
                   (dobby_dummy_func_t*)0);
}

int restore_func(void* origin) {
  return DobbyDestroy(origin);
}

}  // namespace helper
}  // namespace googlemock_extension
