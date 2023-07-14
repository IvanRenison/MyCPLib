#pragma once

#include <IncludeTemplate.hpp>

/* Find the minimum index for witch f is true or it.size() if none if true */
template <typename T> ull binary_search(function<bool(T)> f, vector<T> it) {
  ull lower = 0;
  ull upper = it.size();
  if (f(it[lower])) {
    return lower;
  }
  if (!f(it[upper - 1])) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (f(it[m])) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
}

/* Find the minimum index for witch f is true or upper if none if true */
ull binary_search(function<bool(ull)> f, ull lower, ull upper) {
  if (f(lower)) {
    return lower;
  }
  if (!f(upper - 1)) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (f(m)) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
}
