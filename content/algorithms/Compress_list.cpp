#pragma once

#include <IncludeTemplate.hpp>

pair<ull, vu> compress(vu xs) {
  ull n = xs.size();

  map<ull, vu> xs_map;
  fore(i, 0, n) {
    xs_map[xs[i]].push_back(i);
  }

  vu compressed_xs(n);

  ull i = 0;
  for (auto [x, ks] : xs_map) {
    for (ull k : ks) {
      compressed_xs[k] = i;
    }
    i++;
  }

  return {i - 1, compressed_xs};
}
