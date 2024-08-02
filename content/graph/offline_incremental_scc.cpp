#pragma once

#include <IncludeTemplate.hpp>

// Fuente: https://github.com/programming-team-code/programming_team_code/blob/main/graphs/strongly_connected_components/offline_incremental_scc.hpp

/**
 * @see https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/SCC.h
 * @code{.cpp}
       auto [num_sccs, scc_id] = sccs(adj);
 * @endcode
 */
struct sccs {
  ll num_sccs = 0; /**< number of SCCs */
  /**
   * scc_id[v] = id of SCC containing node v. It satisfies:
   * - 0 <= scc_id[v] < num_sccs
   * - for each edge u -> v: scc_id[u] >= scc_id[v]
   */
  vector<ll> scc_id;
  /**
   * @param adj directed, unweighted graph
   * @time O(n + m)
   * @space this allocates member `scc_id` which is O(n)
   */
  sccs(const vector<vector<ll>>& adj) : scc_id((ll)size(adj), -1) {
    ll n = (ll)size(adj), timer = 1;
    vector<ll> tin(n), st;
    auto dfs = [&](auto&& self, ll v) -> ll {
      ll low = tin[v] = timer++, siz = (ll)size(st);
      st.push_back(v);
      for (ll u : adj[v])
        if (scc_id[u] < 0)
          low = min(low, tin[u] ? tin[u] : self(self, u));
      if (tin[v] == low) {
        for (ll i = siz; i < ((ll)size(st)); i++)
          scc_id[st[i]] = num_sccs;
        st.resize(siz);
        num_sccs++;
      }
      return low;
    };
    for (ll i = 0; i < (n); i++)
      if (!tin[i]) dfs(dfs, i);
  }
};
/**
 * @see [Radecki Algorithm!](https://codeforces.com/blog/entry/91608)
 *
 * @param edge_updates directed edges {u, v} where u -> v
 * @param n number of vertices
 *
 * @returns a vec joins where joins[i] = minimum prefix of edges [0, joins[i]]
 * for eds[i][0] and eds[i][1] to be in the same SCC; iff eds[i][0] and
 * eds[i][1] are never in the same SCC then joins[i] = m
 *
 * @note for self-edges (u, u), joins[i] = -1
 *
 * @time O((n + m) log m)
 * @space O(n + m)
 */
vector<ll> offline_incremental_scc(vuu edge_updates, ll n) {
  ll m = (ll)size(edge_updates);
  vector<ll> ids(n, -1), joins(m, m);
  vector<array<ll, 3>> eds(m);
  for (ll t = 0; t < (m); t++) {
    auto [u, v] = edge_updates[t];
    eds[t] = {(ll)u, (ll)v, t};
  }
  auto divide_and_conquer = [&](auto&& self, auto el, auto er, ll tl, ll tr) {
    ll mid = tl + (tr - tl) / 2;
    vector<ll> vs;
    vector<vector<ll>> adj;
    for (auto it = el; it != er; it++) {
      auto& [u, v, t] = *it;
      for (ll w : {u, v}) {
        if (ids[w] != -1) continue;
        ids[w] = (ll)size(vs);
        vs.push_back(w);
        adj.emplace_back();
      }
      u = ids[u], v = ids[v];
      if (t <= mid) adj[u].push_back(v);
    }
    for (ll v : vs) ids[v] = -1;
    auto scc_id = sccs(adj).scc_id;
    auto split = partition(
        el, er, [&](const auto& ed) { return scc_id[ed[0]] == scc_id[ed[1]]; });
    for (auto it = el; it != split; it++) joins[it->back()] = mid;
    if (tr - tl == 1) return;
    for (auto it = split; it != er; it++) {
      auto& [u, v, t] = *it;
      u = scc_id[u], v = scc_id[v];
    }
    // deallocate to avoid O(m log m) memory
    vector<ll>().swap(vs);
    vector<vector<ll>>().swap(adj);
    vector<ll>().swap(scc_id);
    self(self, el, split, tl, mid);
    self(self, split, er, mid, tr);
  };
  // uses -1 as the lower bound to correctly handle self-edges
  divide_and_conquer(divide_and_conquer, begin(eds), end(eds), -1, m);
  return joins;
}

// Usando union find se puede hacer lo mismo que lo de dynamic connectivity
