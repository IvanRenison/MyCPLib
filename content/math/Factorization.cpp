#pragma once

#include <IncludeTemplate.hpp>

#define MAXN 100001

/* For each number until N get the smallest prime that divides it */
vector<ull> smallest_prime_factors(MAXN);
void sieve(void) {
  for (ull i = 0; i < MAXN; i++) {
    smallest_prime_factors[i] = i;
  }

  for (ull i = 2; i * i < MAXN; i++) {
    if (smallest_prime_factors[i] == i) {
      for (ull j = i * i; j < MAXN; j += i) {
        if (smallest_prime_factors[j] == j) {
          smallest_prime_factors[j] = i;
        }
      }
    }
  }
}

/* smallest_prime_factors has to have the smallest prime factor of each number until x */
vector<pair<ull, ull>> prime_factors(ull x) {
  if (x == 1) {
    return {};
  } else {
    vector<pair<ull, ull>> factors = {{smallest_prime_factors[x], 1}};
    x = ull(x / smallest_prime_factors[x]);
    while (x != 1) {
      if (smallest_prime_factors[x] != factors.back().first) {
        factors.push_back({smallest_prime_factors[x], 0});
      }
      factors.back().second++;
      x = ull(x / smallest_prime_factors[x]);
    }
    return factors;
  }
}
