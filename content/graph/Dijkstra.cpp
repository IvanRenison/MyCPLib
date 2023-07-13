#pragma once

#include <Graph.cpp>
#include <IncludeTemplate.hpp>

/* The return value is a vector of size n, where the i-th element is the
 * vertex that precedes the i-th vertex in the shortest path from s to i.
 * If there is no such path, the i-th element is nullopt.
 */
typedef ull Distance;
vector<optional<Vertex>> Dijkstra(WeightedGraph g, Vertex s) {
  vector<optional<Vertex>> prev(g.n);
  vector<Distance> dist(g.n, numeric_limits<Distance>::max());
  dist[s] = 0;

  priority_queue<
      tuple<Distance, Vertex, Vertex>, vector<tuple<Distance, Vertex, Vertex>>,
      greater<tuple<Distance, Vertex, Vertex>>>
      pq;

  pq.push({0, s, s});

  while (!pq.empty()) {
    auto [d, v, by] = pq.top();
    pq.pop();
    if (prev[v].has_value()) {
      continue;
    }

    prev[v] = by, dist[v] = d;

    for (auto [u, w] : g.adj[v]) {
      if (!prev[u].has_value()) {
        pq.push({d + w, u, v});
      }
    }
  }

  return prev;
  // If you want to return the distances instead of the previous vertices:
  // return dist;
}