/*
 * gmock-helper.h
 *
 * Created on: Sat Dec 17 2022
 *     Author: Tin Tran <realtrantrungtin@gmail.com>
 */

#pragma once

#include <sys/mman.h>
#include <unistd.h>

#include <cstddef>
#include <vector>

namespace googlemock_extension {
namespace helper {

int unprotect_memory(const void* address, size_t length, size_t PAGE_SIZE) {
  void* const page = reinterpret_cast<void*>(
      reinterpret_cast<long long>(address) & (~(PAGE_SIZE - 1)));
  return mprotect(page, length, PROT_READ | PROT_WRITE | PROT_EXEC);
}

int set_jump(void* address, const void* destination,
             std::vector<char>& binary_backup) {
  char* const function = reinterpret_cast<char*>(address);
  binary_backup = std::vector<char>(function, function + 5);
  function[0] = 0xE9;
  std::size_t distance = reinterpret_cast<std::size_t>(destination) -
                         reinterpret_cast<std::size_t>(address) -
                         5;  // For jmp instruction;
  char* const distance_bytes = reinterpret_cast<char*>(&distance);
  std::copy(distance_bytes, distance_bytes + 4, function + 1);
  return 0;
}

template <typename F1, typename F2>
int setJump(F1 address, F2 destination, std::vector<char>& binary) {
  void* function = reinterpret_cast<void*>((std::size_t&)address);
  size_t PAGE_SIZE = getpagesize();
  unprotect_memory(function, PAGE_SIZE, PAGE_SIZE);
  return set_jump(function, reinterpret_cast<void*>((std::size_t&)destination),
                  binary);
}

template <typename F1>
void restoreJump(F1 address, const std::vector<char>& binary) {
  void* function = reinterpret_cast<void*>((std::size_t&)address);
  std::copy(binary.begin(), binary.end(), reinterpret_cast<char*>(function));
}
}  // namespace helper
}  // namespace googlemock_extension
