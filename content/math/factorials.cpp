#pragma once

#include <IncludeTemplate.hpp>
#include "ModularArithmetic.cpp"

ull n_lim = 1e7 + 10;

vm facts(n_lim);
vm inv_facts(n_lim);

void init() {
  facts[0] = Mod(1);
  inv_facts[0] = Mod(1);
  fore(i, 1, n_lim) {
    facts[i] = facts[i - 1] * Mod(i);
    inv_facts[i] = Mod(1) / facts[i];
  }
}

Mod comb(ull n, ull k) {
  if (k > n) {
    return Mod(0);
  } else {
    assert(n < n_lim), assert(k < n_lim);
    return facts[n] * inv_facts[k] * inv_facts[n - k];
  }
}
