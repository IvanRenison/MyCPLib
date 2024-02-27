#pragma once

#include <IncludeTemplate.hpp>

// centroid of a tree is a node that is at the middle of the Nodes
// It has trees of size at most n/2 at each side
struct CentroidTree {
  vector<vi> g;
  ll n;
  vb tk;
  vi fat; // father in centroid decomposition, -1 for total father
  vi szt; // size of subtree
  CentroidTree(vector<vi> g) : g(g), n(g.size()), tk(n, false), fat(n), szt(n) {
    cdfs();
  }
  ll calcsz(ll x, ll f) {
    szt[x] = 1;
    for (auto y : g[x])
      if (y != f && !tk[y])
        szt[x] += calcsz(y, x);
    return szt[x];
  }
  void cdfs(ll x = 0, ll f = -1, ll sz = -1) { // O(n log n)
    if (sz < 0) sz = calcsz(x, -1);
    for (auto y : g[x])
      if (!tk[y] && szt[y] * 2 >= sz) {
        szt[x] = 0;
        cdfs(y, f, sz);
        return;
      }
    tk[x] = true;
    fat[x] = f;
    for (auto y : g[x])
      if (!tk[y]) cdfs(y, x);
  }
};
