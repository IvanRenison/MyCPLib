#pragma once

#include <IncludeTemplate.hpp>

const ull MAXN = 1e6;

/* For each number until N get the smallest prime that divides it */
vu small_primes(MAXN + 1);
void sieve(void) {
  for (ull i = 1; i < MAXN + 1; i++) {
    if (i % 2 == 0) {
      small_primes[i] = 2;
    } else {
      small_primes[i] = i;
    }
  }

  for (ull i = 3; i * i < MAXN + 1; i += 2) {
    if (small_primes[i] == i) {
      for (ull j = i * i; j < MAXN + 1; j += i) {
        if (small_primes[j] == j) {
          small_primes[j] = i;
        }
      }
    }
  }
}

/* small_primes has to have the smallest prime factor of each number until x */
vuu prime_factors(ull x) {
  if (x == 1) {
    return {};
  } else {
    vuu factors = {{small_primes[x], 1}};
    x = ull(x / small_primes[x]);
    while (x != 1) {
      if (small_primes[x] != factors.back().first) {
        factors.push_back({small_primes[x], 0});
      }
      factors.back().second++;
      x = ull(x / small_primes[x]);
    }
    return factors;
  }
}
