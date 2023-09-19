#pragma once

#include <IncludeTemplate.hpp>

#define MAXN 100001

/* For each number until N get the smallest prime that divides it */
vu smallest_prime_factors(MAXN);
void sieve(void) {
  for (ull i = 1; i < MAXN; i++) {
    if (i % 2 == 0) {
      smallest_prime_factors[i] = 2;
    } else {
      smallest_prime_factors[i] = i;
    }
  }

  for (ull i = 3; i * i < MAXN; i += 2) {
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
vuu prime_factors(ull x) {
  if (x == 1) {
    return {};
  } else {
    vuu factors = {{smallest_prime_factors[x], 1}};
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
