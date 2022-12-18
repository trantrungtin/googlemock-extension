# Extension for Google Mock

## Features

*   Support non-virtual methods
*   Same functionality as google mock

## Google Mock

Details and examples of Google Mock can be found here:

*   [gMock for Dummies](https://google.github.io/googletest/gmock_for_dummies.html)
*   [Legacy gMock FAQ](https://google.github.io/googletest/gmock_faq.html)
*   [gMock Cookbook](https://google.github.io/googletest/gmock_cook_book.html)
*   [gMock Cheat Sheet](https://google.github.io/googletest/gmock_cheat_sheet.html)

## Use cases

You have some non-virutal methods needed to mock.

```c++
class Demo {
 public:
  int add(int a, int b); /* Need to mock this method */
  int mul(int a, int b, int c); /* Need to mock this method */
  virtual int sub(int a, int b);
};
```

Mock your functions with macro `MOCK_METHOD_EX`

```c++
#include "gmock-extension.h"

class MockDemo : public Demo {
 public:
  MockDemo(){};
  MOCK_METHOD(int, sub, (int a, int b));
  MOCK_METHOD_EX(int, add, (int a, int b)); /* Same style as google mock */
  MOCK_METHOD_EX(int, mul, (int a, int b, int c));
};
```

Used `EXPECT_CALL_EX`, `ON_CALL_EX` to setup your method's behavior.

```c++
TEST_F(DemoTest, TestAdd) {
  EXPECT_CALL_EX(*mMock, add(_, _)).WillOnce([] { return 10; });
  EXPECT_EQ(10, mMock->add(2, 3));
}
```

Checkout examples for more details.

## Build

```bash
git clone --recurse-submodules https://github.com/trantrungtin/googlemock-extension.git
cd googlemock-extension
mkdir -p build && cd build
cmake .. -DCMAKE_OSX_ARCHITECTURES=arm64 && make && bin/gmocke_examples
```
