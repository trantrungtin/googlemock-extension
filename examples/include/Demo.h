/*
 * Demo.h
 *
 * Created on: Sat Dec 17 2022
 *     Author: Tin Tran <realtrantrungtin@gmail.com>
 */


#pragma once

class Demo {
 public:
  int add(int a, int b);
  int mul(int a, int b, int c);
  virtual int sub(int a, int b);
};