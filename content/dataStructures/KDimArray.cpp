#pragma once

#include <IncludeTemplate.hpp>

struct KDimArray {
  typedef ull T;
  vu ds;
  vector<T> elems;
  KDimArray() {};
  KDimArray(const vu& ds) : ds(ds) {
    ull p = 1;
    for(ull d : ds) {
      p *= d;
    }
    elems = vector<T>(p);
  }
  T operator[](const vu& id) const {
    ull idx = 0;
    fore(i, 0, ds.size()) {
      idx *= ds[i];
      idx += id[i];
    }
    return elems[idx];
  }
  T& operator[](const vu& id) {
    ull idx = 0;
    fore(i, 0, ds.size()) {
      idx *= ds[i];
      idx += id[i];
    }
    return elems[idx];
  }

  void nextIndex(vu& is) const {
    ull n = is.size();
    for(ull i = n-1; i < n; i--) {
      is[i]++;
      if (is[i] == ds[i]) {
        is[i] = 0;
      } else {
        break;
      }
    }
  }
};
