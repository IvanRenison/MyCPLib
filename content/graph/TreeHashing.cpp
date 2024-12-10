#pragma once

#include <IncludeTemplate.hpp>

// Arithmetic mod 2^64-1 from kactlpp
struct H {
  ull x; H(ull x=0) : x(x) {}
  H operator+(H o) { return x + o.x + (x + o.x < x); }
  H operator-(H o) { return *this + ~o.x; }
  H operator*(H o) { auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull)(m >> 64); }
  ull get() const { return x + !~x; }
  bool operator==(H o) const { return get() == o.get(); }
  bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ull)1e11+3; // (order ~ 3e9; random also ok)

// Struct that computes rooted tree hashes for each subtree in O(N)
// Idea: https://codeforces.com/blog/entry/113465
struct TreeHash {
  ull n;
  vector<vu> adj;
  vector<H> hashes;

  TreeHash(vector<vu>& adj_, ull root = 0) : n(adj_.size()), adj(adj_), hashes(n) {
    dfs(root, -1);
  }

  H dfs(ull u, ull p) {
    vector<H> suns_hashes;
    for (ull v : adj[u]) if (v != p) {
      suns_hashes.push_back(dfs(v, u));
    }
    sort(ALL(suns_hashes));
    H hash = 42;
    H pow = 1;
    fore(i, 0, suns_hashes.size()) {
      hash = hash * C + suns_hashes[i] * suns_hashes[i] + suns_hashes[i] * pow;
      pow = pow * C;
    }
    return hashes[u] = hash;
  }
};
