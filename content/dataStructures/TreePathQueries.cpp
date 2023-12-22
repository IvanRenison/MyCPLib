#pragma once

#include <IncludeTemplate.hpp>

struct PathQueries { // O(n log n) preprocessing, O(log n) query
  typedef ull T;
  constexpr static T NEUT = 0;
  T op(const T& a, const T& b) {
    return max(a, b);
  } // associative and commutative
  ull n, K;
  vector<vu> anc; // remove & for edge queries or if instance lives longer
  vector<vector<T>> part;
  vu dep;
  // NODES
  PathQueries(const vector<vu>& g, vector<T>& vals)
      : n(g.size()), K(64 - __builtin_clzll(n)), anc(K, vu(n)), part(K, vector<T>(n, NEUT)), dep(n) {
  // EDGES
  // PathQueries(vector<vector<pair<ll, T>>> &_g)
  //     : n(_g.size()), K(64 - __builtin_clzll(n)), anc(K, vi(n)), part(K, vector<T>(n, NEUT)), dep(n) {
  //   vector<vu> g(n);
  //   fore(u, 0, n) for (auto [v, data] : _g[u]) g[u].pb(v);
    anc[0][0] = inf;
    vu s = {0};
    while (!s.empty()) {
      ull u = s.back();
      s.pop_back();
      for (ull v : g[u]) {
        if (v != anc[0][u]) {
          anc[0][v] = u, dep[v] = dep[u] + 1, s.push_back(v);
        }
      }
    }
    part[0] = vals;
    // fore(u, 0, n) for (auto [v, data] : _g[u]) part[0][dep[u] > dep[v] ? u : v] = data; // EDGES
    fore(k, 1, K) fore(v, 0, n) {
      if (anc[k - 1][v] != inf) {
        anc[k][v] = anc[k - 1][anc[k - 1][v]],
        part[k][v] = op(part[k - 1][v], part[k - 1][anc[k - 1][v]]);
      } else {
        anc[k][v] = inf;
      }
    }
  }
  T query(ull u, ull v) {
    if (dep[u] < dep[v])
      swap(u, v);
    T ans = NEUT;
    for (ull k = K - 1; k < K; k--)
      if (dep[u] >= dep[v] + (1 << k))
        ans = op(ans, part[k][u]), u = anc[k][u];
    // if (u == v) return ans; // edge queries
    if (u == v)
      return op(ans, part[0][u]); // node queries
    for (ull k = K - 1; k < K; k--)
      if (anc[k][u] != anc[k][v])
        ans = op(ans, op(part[k][u], part[k][v])), u = anc[k][u], v = anc[k][v];
    ans = op(ans, op(part[0][u], part[0][v]));
    // return ans; // edge queries
    return op(ans, part[0][anc[0][u]]); // node queries
  }
};
