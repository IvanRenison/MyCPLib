#pragma once

#include <IncludeTemplate.hpp>

#include <Reverse_priority_queue.cpp>

/* The return value is a vector of size n, where the i-th element is the
 * vertex that precedes the i-th vertex in the shortest path from s to i.
 * If there is no such path, the i-th element is inf.
 * Also the s-th element is inf.
 */
typedef ull Dis;
vu Dijkstra(vector<vuu> adj, ull s) {
  ull n = adj.size();
  vu prev(n, inf);
  vector<Dis> dist(n, numeric_limits<Dis>::max());

  rpriority_queue<tuple<Dis, ull, ull>> q;

  q.push({0, s, inf});

  while (!q.empty()) {
    auto [d, v, by] = q.top();
    q.pop();
    if (prev[v] != inf) {
      continue;
    }

    prev[v] = by, dist[v] = d;

    for (auto [u, w] : adj[v]) {
      if (prev[u] == inf) {
        q.push({d + w, u, v});
      }
    }
  }

  return prev;
  // If you want to return the distances instead of the previous vertices:
  // return dist;
}