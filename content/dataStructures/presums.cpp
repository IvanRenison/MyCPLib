#pragma once

#include <IncludeTemplate.hpp>

struct presums {
  typedef ull T;
  T op(T a, T b) { return a + b; }
  T rev(T a, T b) { return a - b; }
  constexpr static T neut = 0;
  // rev(op(a, b), b) = a

  ull n;
  vector<T> as;

  presums(ull n) : n(n), as(n + 1) {}

  void update(ull i, ull j, T v) { // [i, j)
    as[i] = op(as[i], v);
    as[j] = rev(as[j], v);
  }

  vector<T> build() {
    vector<T> ans(n);
    ans[0] = as[0];
    fore(i, 1, n) {
      ans[i] = op(ans[i - 1], as[i]);
    }
    return ans;
  }
};
