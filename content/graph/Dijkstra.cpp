#pragma once

#include <IncludeTemplate.hpp>

#include <Graph.cpp>
#include <Reverse_priority_queue.cpp>

/* The return value is a vector of size n, where the i-th element is the
 * vertex that precedes the i-th vertex in the shortest path from s to i.
 * If there is no such path, the i-th element is nullopt.
 */
typedef ull Distance;
vector<optional<Vertex>> Dijkstra(WeightedGraph g, Vertex s) {
  vector<optional<Vertex>> prev(g.n);
  vector<Distance> dist(g.n, numeric_limits<Distance>::max());
  dist[s] = 0;

  rpriority_queue<tuple<Distance, Vertex, Vertex>> q;

  q.push({0, s, s});

  while (!q.empty()) {
    auto [d, v, by] = q.top();
    q.pop();
    if (prev[v].has_value()) {
      continue;
    }

    prev[v] = by, dist[v] = d;

    for (auto [u, w] : g.adj[v]) {
      if (!prev[u].has_value()) {
        q.push({d + w, u, v});
      }
    }
  }

  return prev;
  // If you want to return the distances instead of the previous vertices:
  // return dist;
}