#include <iostream>

#include "Demo.h"
#include "gmock/gmock.h"
#include "gmock/internal/gmock-pp.h"
#include "gmock/gmock-spec-builders.h"
#include "gmock/gmock-matchers.h"
#include "set_function_jump.h"

using namespace std;
using namespace testing;

typedef std::function<void(bool)> SetupFunc;

struct GmockExLifecycle {
    GmockExLifecycle(SetupFunc&& func)
      : mFunc(std::move(func)) {
        func(true);
    }
    ~GmockExLifecycle() {
        mFunc(false);
    }
private:
    SetupFunc mFunc;
};
    
#define STR_(X) #X
#define XSTR(X) STR_(X)

#define GMOCK_EX_CAT(a, b) a##b
#define GMOCK_EX_INTERNAL_A_MATCHER_ARGUMENT(_i, _Data, _Elem) \
  GMOCK_PP_COMMA_IF(_i) \
  GMOCK_EX_CAT(_Data, _i) GMOCK_EX_CAT(_##_Data, _i)

#define GMOCK_EX_INTERNAL_A_TEMPLATE_ARGUMENT(_i, _Data, _Elem) \
  GMOCK_PP_COMMA_IF(_i) \
  _Data GMOCK_EX_CAT(T, _i)

#define GMOCK_EX_INTERNAL_MOCK_METHOD_IMPL(_N, _MethodName)                 \
  template<GMOCK_PP_REPEAT(GMOCK_EX_INTERNAL_A_TEMPLATE_ARGUMENT, typename, _N)> \
  GmockExLifecycle&& GMOCK_EX_CAT(GMOCK_EX_SETUP_, _MethodName)(            \
      GMOCK_PP_REPEAT(GMOCK_EX_INTERNAL_A_MATCHER_ARGUMENT, T, _N)) {       \
    static std::vector<char> binary;                                        \
    static bool isMock = false;                                             \
    SetupFunc setupMock = [&](bool mock) {                                  \
      if (mock) {                                                           \
        if (isMock) {                                                       \
          return;                                                           \
        }                                                                   \
        isMock = true;                                                      \
        SetFunctionJump(                                                    \
            &std::remove_pointer_t<decltype(this)>::add,                    \
            &std::remove_pointer_t<decltype(this)>::GMOCK_EX_add,    \
            binary);                                                        \
        printf("setup mock\n");                                             \
      } else {                                                              \
        if (isMock) {                                                       \
          isMock = false;                                                   \
          RestoreJump(&std::remove_pointer_t<decltype(this)>::add, binary); \
          printf("remove mock\n");                                          \
        }                                                                   \
      }                                                                     \
    };                                                                      \
    GmockExLifecycle instance(std::forward<SetupFunc&&>(setupMock));        \
    return std::move(instance);                                             \
  }

#define GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_0(_Ret, _Args)
#define GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_1(_Ret, _Args)

#define GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_2(_MethodName, _Args) \
  GMOCK_EX_INTERNAL_MOCK_METHOD_IMPL(GMOCK_PP_NARG0 _Args, _MethodName)

#define MOCK_METHOD_EX(...) \
  GMOCK_PP_VARIADIC_CALL(GMOCK_EX_INTERNAL_MOCK_METHOD_ARG_, __VA_ARGS__)

#define AAA MOCK_METHOD_EX(add, (int a, int b));
// #pragma message "content: " XSTR(AAA)

class MockDemo : public Demo {
public:
  MockDemo(){};
  MOCK_METHOD(int, sub, (int a, int b));
//   MOCK_METHOD_EX(int, add, (int a, int b));
//   void test() {
//     printf("%p", &std::remove_pointer_t<decltype(this)>::add);
//   }
    // template <typename F>
    /*
    testing::internal::TypedExpectation<int()>& GMOCK_EXTENSION_INTERNAL_SETUP_add(bool willMock, const char* file, int line, const char* obj, const char* call) {
        decltype(this) thisParent = this;
        struct GMOCK_EXTENSION_INTERNAL_STRUCT_add {
            MOCK_METHOD0(add, int());
            void mock(decltype(thisParent) currParent) {
                SetFunctionJump(&std::remove_pointer_t<decltype(currParent)>::add
                    ,&std::remove_pointer_t<decltype(this)>::add
                    ,binary);
            }
            void unmock(decltype(thisParent) currParent) {
                RestoreJump(&std::remove_pointer_t<decltype(currParent)>::add, binary);
            }
            std::vector<char> binary;
        };
        static GMOCK_EXTENSION_INTERNAL_STRUCT_add instance;
        if (willMock) {
            instance.mock(this);
        } else {
            instance.unmock(this);
        }
        // return EXPECT_CALL(instance, add());
        // return (instance.gmock_add).InternalExpectedAt(__FILE__, __LINE__, #instance, #add);
        return ((instance).gmock_add()).InternalExpectedAt(file, line, obj, call);
    }
    */

    MOCK_METHOD(int, GMOCK_EX_add, (int a, int b));
    // MOCK_METHOD_EX(add, (int a, int b));
    void test() {
      printf("add1: %p\n", &std::remove_pointer_t<decltype(this)>::add);                                                     
      printf("GMOCK_EX_add1: %p\n", &std::remove_pointer_t<decltype(this)>::GMOCK_EX_add);                                                     
    }
    template <typename T0, typename T1>
    GmockExLifecycle GMOCK_EX_SETUP_add(T0 _T0, T1 _T1) {
      static std::vector<char> binary;
      static bool isMock = false;
      printf("this: %p\n", this);
      SetupFunc setupMock = [&](bool mock) {
        if (mock) {
          if (isMock) {
            return;
          }
          isMock = true;
          printf("add2: %p\n", &std::remove_pointer_t<decltype(this)>::add);
          printf("GMOCK_EX_add2: %p\n",
                 &std::remove_pointer_t<decltype(this)>::GMOCK_EX_add);
          SetFunctionJump(
              &std::remove_pointer_t<decltype(this)>::add,
              &std::remove_pointer_t<decltype(this)>::GMOCK_EX_add,
              binary);
          printf("setup mock\n");
        } else {
          if (isMock) {
            isMock = false;
            RestoreJump(&std::remove_pointer_t<decltype(this)>::add, binary);
            printf("remove mock\n");
          }
        }
      };
      GmockExLifecycle instance(std::move(setupMock));
      return instance;
      // GmockExLifecycle instance(std::forward<SetupFunc&&>(setupMock));
      // return std::move(instance);
    }

    // GmockExLifecycle&& GMOCK_EXTENSION_SETUP_add(GMOCK_INTERNAL_MOCK_METHOD_SETUP(int, (int a, int b))) {
    //     static vector<char> binary;
    //     static bool isMock = false;
    //     SetupFunc setupMock = [&](bool mock) {
    //         if (mock) {
    //             if (isMock) {
    //                 return;
    //             }
    //             isMock = true;
    //             SetFunctionJump(&std::remove_pointer_t<decltype(this)>::add
    //                     ,&std::remove_pointer_t<decltype(this)>::GMOCK_EXTENSION_add
    //                     ,binary);
    //             printf("setup mock\n");
    //         } else {
    //             if (isMock) {
    //                 isMock = false;
    //                 RestoreJump(&std::remove_pointer_t<decltype(this)>::add, binary);
    //                 printf("remove mock\n");
    //             }
    //         }
    //     };
    //     GmockExLifecycle instance(std::forward<SetupFunc&&>(setupMock));
    //     return std::move(instance);
    // }
    /*
    void GMOCK_EXTENSION_SETUP_add(bool mock) {
        static vector<char> binary;
        static bool isMock = false;
        if (mock) {
            if (isMock) {
                return;
            }
            isMock = true;
            SetFunctionJump(&std::remove_pointer_t<decltype(this)>::add
                    ,&std::remove_pointer_t<decltype(this)>::GMOCK_EXTENSION_add
                    ,binary);
        } else {
            if (isMock) {
                isMock = false;
                RestoreJump(&std::remove_pointer_t<decltype(this)>::add, binary);
            }
        }
    }
    */

  /*
  struct Fake_global_getString {
    MOCK_METHOD0(global_getString, string());
    std::vector<char> binary_backup;
  };
  static Fake_global_getString* fake_global_getString;
  struct Fake_memder_global_getString {
    string Wrap_global_getString() {
      return fake_global_getString->global_getString();
    }
  };
  */
};

// fake_global_getString = new Fake_global_getString();
// SetFunctionJump(&Simple::getString,
// &Fake_memder_global_getString::Wrap_global_getString,
// fake_global_getString->binary_backup);

