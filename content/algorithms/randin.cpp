#pragma once

#include <IncludeTemplate.hpp>

template <typename T> T randin(T a, T b) {
  static random_device rd;
  static mt19937_64 gen(rd());
  uniform_int_distribution<T> dis(a, b - 1);
  return dis(gen);
}
