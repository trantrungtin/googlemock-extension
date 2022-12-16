#include <iostream>

#include "Demo.h"
#include "gmock-extension.h"

class MockDemo : public Demo {
 public:
  MockDemo(){};
  MOCK_METHOD(int, sub, (int a, int b));
  MOCK_METHOD_EX(int, add, (int a, int b));
  MOCK_METHOD_EX(int, mul, (int a, int b, int c));
};
