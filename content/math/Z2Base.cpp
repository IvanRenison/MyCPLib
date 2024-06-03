#pragma once

#include <IncludeTemplate.hpp>

struct Z2Base {
  vu bs;
  ull red(ull x) const {
    for (ull b : bs) {
      x = min(x, x ^ b);
    }
    return x;
  }
  void add(ull x) {
    x = red(x);
    if (x != 0) {
      bs.push_back(x);
    }
  }
  bool in(ull x) const {
    return red(x) == 0;
  }
  ull dim() const {
    return bs.size();
  }
};
