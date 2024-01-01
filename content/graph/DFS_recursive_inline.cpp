// n → size of the graph, adj → adjacency list
vb visited(n, false);
function<void(ull)> dfs = [&](ull u) {
  visited[u] = true;

  for (ull v : adj[u]) {
    if (!visited[v]) {
      dfs(v);
    }
  }

};