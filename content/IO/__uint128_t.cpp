#pragma once

#include <IncludeTemplate.hpp>

istream& operator>>(istream& is, __uint128_t& value) {
  unsigned long long x;
  is >> x;
  value = x;
  return is;
}

ostream& operator<<(ostream& os, __uint128_t value) {
  if (value >= 10) {
    os << (value / 10);
  }
  os << (char)(value % 10 + '0');
  return os;
}
