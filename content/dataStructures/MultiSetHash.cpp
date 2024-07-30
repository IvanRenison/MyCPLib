#pragma once

#include <IncludeTemplate.hpp>

ull random(ull x) {
  static random_device rd;
  static mt19937_64 gen(rd());
  static uniform_int_distribution<ull> dis(0, -1);

  map<ull, ull> mem;

  if (mem.count(x)) {
    return mem[x];
  } else {
    return mem[x] = dis(gen);
  }
}

struct MultiSetHash {
  ull x;
  MultiSetHash() : x(0) {}

  void insert(ull y) {
    x += random(y);
  }
  void erase(ull y) {
    x -= random(y);
  }
  bool operator==(MultiSetHash o) const {
    return x == o.x;
  }
  bool empty() {
    return x == 0;
  }
  MultiSetHash operator+(MultiSetHash o) const {
    MultiSetHash res;
    res.x = x + o.x;
    return res;
  }
  MultiSetHash operator-(MultiSetHash o) const {
    MultiSetHash res;
    res.x = x - o.x;
    return res;
  }

};

/* struct MultiSetHash { // Useful for debugging
  map<ull, ull> x;
  MultiSetHash() {}

  void insert(ull y) {
    x[y]++;
    if (x[y] == 0) {
      x.erase(y);
    }
  }
  void erase(ull y) {
    x[y]--;
    if (x[y] == 0) {
      x.erase(y);
    }
  }
  bool operator==(MultiSetHash o) const {
    return x == o.x;
  }
  bool empty() {
    return x.empty();
  }
  MultiSetHash operator+(MultiSetHash o) const {
    MultiSetHash res = *this;
    for (auto& [k, v] : o.x) {
      res.x[k] += v;
      if (res.x[k] == 0) {
        res.x.erase(k);
      }
    }
    return res;
  }
  MultiSetHash operator-(MultiSetHash o) const {
    MultiSetHash res = *this;
    for (auto& [k, v] : o.x) {
      res.x[k] -= v;
      if (res.x[k] == 0) {
        res.x.erase(k);
      }
    }
    return res;
  }

}; */
