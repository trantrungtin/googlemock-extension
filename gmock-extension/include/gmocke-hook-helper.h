/*
 * gmock-jump-helper.h
 *
 * Created on: Sun Dec 18 2022
 *     Author: Tin Tran <realtrantrungtin@gmail.com>
 */

#pragma once

namespace googlemock_extension {
namespace helper {

typedef void (*gmocke_dummy_func_t)();

template <typename F1, typename F2>
static int replace_func(F1 origin, F2 replace,
                        gmocke_dummy_func_t* backup);

template <typename F1, typename F2>
static int replace_func(F1 origin, F2 replace);

static int restore_func(void* origin);

}  // namespace helper
}  // namespace googlemock_extension