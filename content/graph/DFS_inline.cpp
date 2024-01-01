// n → size of the graph, adj → adjacency list
vb vis(n, false);
vis[0] = true;
vu s = {0};
while (!s.empty()) {
  ull u = s.back();
  s.pop_back();

  for (ull v : adj[u]) {
    if (!vis[v]) {
      vis[v] = true;
      s.push_back(v);
    }
  }
}
