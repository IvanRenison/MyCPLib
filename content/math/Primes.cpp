#pragma once

#include <IncludeTemplate.hpp>

#define MAXN 100001

vector<bool> prime(MAXN, true);
void sieve(void) {
  prime[0] = false, prime[1] = false;
  for (ull i = 4; i < MAXN; i += 2) {
    prime[i] = false;
  }

  for (ull i = 3; i * i < MAXN; i += 2) {
    if (prime[i]) {
      for (ull j = i * i; j < MAXN; j += i) {
        prime[j] = false;
      }
    }
  }
}
