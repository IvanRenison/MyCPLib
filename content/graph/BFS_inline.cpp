vu fathers(N, inf);
queue<ull> q;
q.push(0);
fathers[0] = 0;

while (!q.empty()) {
  ull u = q.front();
  q.pop();

  for (ull v : adj[u]) {
    if (fathers[v] == inf) {
      fathers[v] = u;
      q.push(v);
    }
  }
}