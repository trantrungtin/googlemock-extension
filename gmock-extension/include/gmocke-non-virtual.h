/*
 * gmock-non-virtual.h
 *
 * Created on: Sat Dec 17 2022
 *     Author: Tin Tran <realtrantrungtin@gmail.com>
 */

#pragma once

#include "gmock/gmock-matchers.h"
#include "gmock/gmock-spec-builders.h"
#include "gmock/gmock.h"
#include "gmock/internal/gmock-pp.h"
#include "gmocke-hook-helper.h"

using namespace testing;

namespace googlemock_extension {
typedef std::function<void(bool)> SetupFunc;

struct GmockExLifecycle {
  GmockExLifecycle(SetupFunc&& func) : mFunc(func) { func(true); }
  ~GmockExLifecycle() { mFunc(false); }

 private:
  SetupFunc mFunc;
};
};  // namespace googlemock_extension

#define GMOCK_EX_CAT(a, b) a##b
#define GMOCK_EX_INTERNAL_A_MATCHER_ARGUMENT(_i, _Data, _Elem) \
  GMOCK_PP_COMMA_IF(_i)                                        \
  GMOCK_EX_CAT(_Data, _i) GMOCK_EX_CAT(_##_Data, _i)

#define GMOCK_EX_INTERNAL_A_TEMPLATE_ARGUMENT(_i, _Data, _Elem) \
  GMOCK_PP_COMMA_IF(_i)                                         \
  _Data GMOCK_EX_CAT(T, _i)

#define GMOCK_EX_REF_METHOD(X) std::remove_pointer_t<decltype(this)>::X

#define GMOCK_EX_INTERNAL_DEFAULT_IML(_MethodName)                         \
  static bool isMock = false;                                              \
  googlemock_extension::SetupFunc setupMock = [&](bool mock) {             \
    if (mock) {                                                            \
      if (isMock) {                                                        \
        return;                                                            \
      }                                                                    \
      isMock = true;                                                       \
      GMOCK_EX_REPLACE_FUNC(&GMOCK_EX_REF_METHOD(_MethodName),             \
                            &GMOCK_EX_REF_METHOD(GMOCK_EX_##_MethodName)); \
    } else {                                                               \
      if (isMock) {                                                        \
        isMock = false;                                                    \
        GMOCK_EX_RESTORE_FUNC(&GMOCK_EX_REF_METHOD(_MethodName));         \
      }                                                                    \
    }                                                                      \
  };                                                                       \
  googlemock_extension::GmockExLifecycle instance(std::move(setupMock));   \
  return instance;

#define GMOCK_EX_INTERNAL_MOCK_METHOD_IMPL(_N, _MethodName)                  \
  template <GMOCK_PP_REPEAT(GMOCK_EX_INTERNAL_A_TEMPLATE_ARGUMENT, typename, \
                            _N)>                                             \
  googlemock_extension::GmockExLifecycle GMOCK_EX_CAT(GMOCK_EX_SETUP_,       \
                                                      _MethodName)(          \
      GMOCK_PP_REPEAT(GMOCK_EX_INTERNAL_A_MATCHER_ARGUMENT, T, _N)) {        \
    GMOCK_EX_INTERNAL_DEFAULT_IML(_MethodName)                               \
  }

#define GMOCK_EX_INTERNAL_MOCK_METHOD_DEFAULT_IMPL(_MethodName)        \
  googlemock_extension::GmockExLifecycle GMOCK_EX_CAT(GMOCK_EX_SETUP_, \
                                                      _MethodName)() { \
    GMOCK_EX_INTERNAL_DEFAULT_IML(_MethodName)                         \
  }

#define MOCK_METHOD_EX(...) \
  GMOCK_PP_VARIADIC_CALL(GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_, __VA_ARGS__)

#define GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_1(...) \
  GMOCK_EX_INTERNAL_WRONG_ARITY(__VA_ARGS__)

#define GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_2(...) \
  GMOCK_EX_INTERNAL_WRONG_ARITY(__VA_ARGS__)

#define GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_3(_Ret, _MethodName, _Args) \
  GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_4(_Ret, _MethodName, _Args, ())

#define GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_4(_Ret, _MethodName, _Args, _Spec)   \
  GMOCK_INTERNAL_MOCK_METHOD_ARG_4(_Ret, GMOCK_EX_CAT(GMOCK_EX_, _MethodName), \
                                   _Args, _Spec);                              \
  GMOCK_EX_INTERNAL_MOCK_METHOD_IMPL(GMOCK_PP_NARG0 _Args, _MethodName);       \
  GMOCK_EX_INTERNAL_MOCK_METHOD_DEFAULT_IMPL(_MethodName);

#define GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_5(...) \
  GMOCK_EX_INTERNAL_WRONG_ARITY(__VA_ARGS__)

#define GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_6(...) \
  GMOCK_EX_INTERNAL_WRONG_ARITY(__VA_ARGS__)

#define GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_7(...) \
  GMOCK_EX_INTERNAL_WRONG_ARITY(__VA_ARGS__)

#define GMOCK_EX_INTERNAL_WRONG_ARITY(...)                                   \
  static_assert(                                                             \
      false,                                                                 \
      "MOCK_METHOD_EX must be called with 3 or 4 arguments. _Ret, "          \
      "_MethodName, _Args and optionally _Spec. _Args and _Spec must be "    \
      "enclosed in parentheses. If _Ret is a type with unprotected commas, " \
      "it must also be enclosed in parentheses.")

#define UNIQUE_NAME(base) GMOCK_EX_CAT(base, __COUNTER__)

#define GMOCK_EXPECT_CALL_EX_IMPL_(obj, call)         \
  googlemock_extension::GmockExLifecycle UNIQUE_NAME( \
      googlemock_extension_VAR) = ((obj).GMOCK_EX_CAT(GMOCK_EX_SETUP_, call))

#define GMOCK_ON_CALL_EX_IMPL_(obj, call)             \
  googlemock_extension::GmockExLifecycle UNIQUE_NAME( \
      googlemock_extension_VAR) = (obj).GMOCK_EX_CAT(GMOCK_EX_SETUP_, call)()

#define EXPECT_CALL_EX(obj, call)        \
  GMOCK_EXPECT_CALL_EX_IMPL_(obj, call); \
  EXPECT_CALL(obj, GMOCK_EX_CAT(GMOCK_EX_, call))

#define ON_CALL_EX(obj, call)        \
  GMOCK_ON_CALL_EX_IMPL_(obj, call); \
  ON_CALL(obj, GMOCK_EX_CAT(GMOCK_EX_, call))
