#pragma once

#include <IncludeTemplate.hpp>

#include "ModularArithmetic.cpp"

const ull maxn = 1e5; // CHANGE

vm facts(maxn + 1);
vm inv_facts(maxn + 1);

void init() {
  facts[0] = Mod(1);
  fore(i, 1, maxn + 1) {
    facts[i] = facts[i - 1] * Mod(i);
  }
  fore(i, 0, maxn + 1) {
    inv_facts[i] = Mod(1) / facts[i];
  }
}

// ys[i] = f(i), returns f(x)
// O(n log(n)) for Mod, O(n) for ld
Mod interpolate(vm ys, Mod x) {
  ll n = ys.size();

  if (x.x < n) {
    return ys[x.x];
  }

  Mod prod_num = Mod(1);
  fore(i, 0, n) {
    Mod xi = Mod(i);
    prod_num = prod_num * (x - xi);
  }

  Mod ans = Mod(0);

  fore(i, 0, n) {
    Mod xi = Mod(i), yi = ys[i];
    Mod term = yi;
    term = term * prod_num / (x - xi);
    term = term * inv_facts[i] * inv_facts[n - 1 - i];
    if ((n - 1 - i) % 2 == 1) {
      term = term * Mod(-1);
    }

    ans = ans + term;
  }

  return ans;
}