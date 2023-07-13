#pragma once

#include <IncludeTemplate.hpp>

typedef ull Vertex;
typedef tuple<Vertex, Vertex> Edge;

struct Graph {
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vector<Vertex>> adj;

  Graph(ull n, vector<Edge> edges)
      : n(n), m(edges.size()), edges(edges), adj(n) {
    for (auto [u, v] : edges) {
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }
};

struct DirectedGraph {
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vector<Vertex>> adj_fordward;
  vector<vector<Vertex>> adj_backward;

  DirectedGraph(ull n, vector<Edge> edges)
      : n(n), m(edges.size()), edges(edges), adj_fordward(n), adj_backward(n) {
    for (auto [u, v] : edges) {
      adj_fordward[u].push_back(v);
      adj_backward[v].push_back(u);
    }
  }
};

pair<ull, vector<Edge>> readGraph() {
  ull n, m;
  cin >> n >> m;

  vector<Edge> edges(m);
  fore(i, 0, m) {
    ull u, v;
    cin >> u >> v;
    edges[i] = {u - 1, v - 1};
  }

  return {n, edges};
}

/* WeightedGraph */

typedef ull Vertex;
typedef ull Weight;
typedef tuple<Vertex, Vertex, Weight> wEdge;

struct WeightedGraph {
  ull n;
  ull m;
  vector<wEdge> edges;
  vector<vector<pair<Vertex, Weight>>> adj;

  WeightedGraph(ull n, vector<wEdge> edges)
      : n(n), m(edges.size()), edges(edges), adj(n) {
    for (auto [u, v, w] : edges) {
      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
    }
  }
};

pair<ull, vector<wEdge>> readWeightedGraph() {
  ull n, m;
  cin >> n >> m;

  vector<wEdge> edges(m);
  fore(i, 0, m) {
    ull u, v, w;
    cin >> u >> v >> w;
    edges[i] = {u - 1, v - 1, w};
  }

  return {n, edges};
}
