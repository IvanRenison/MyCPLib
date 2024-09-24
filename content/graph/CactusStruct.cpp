#pragma once

#include <IncludeTemplate.hpp>

vector<vu> findCycles(const vector<vu>& adj) {
  ull n = adj.size();

  vector<vu> ans;

  vb vis(n, false);
  vector<set<ull>> cycle_added(n);
  vu par(n, inf);

  function<void(ull)> dfs = [&](ull u) {
    vis[u] = true;
    for (ull v : adj[u]) if (!cycle_added[u].count(v)) {
      if (!vis[v]) {
        par[v] = u;
        dfs(v);
      } else if (v != par[u]) {
        vu cycle;
        for (ull x = u; x != v; x = par[x]) {
          //assert(x != inf);
          cycle.push_back(x);
        }
        cycle.push_back(v);
        cycle_added[v].insert(u);
        ans.push_back(move(cycle));
      }
    }
  };

  dfs(0);
  //fore(u, 0, n) {
  //  //assert(vis[u]);
  //}

  return ans;
}

struct Cactus {
  ull head; // Id of head node
  vector<Cactus> children;
  vector<vector<Cactus>> cycles;
};

Cactus constructCactus(ull n, const vuu& edges) {
  vector<vu> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vector<vu> cycles = findCycles(adj);
  vector<vu> cycles_per_node(n);
  fore(i, 0, cycles.size()) {
    for (ull u : cycles[i]) {
      cycles_per_node[u].push_back(i);
    }
  }

  vb vis(n, false);
  vb cycle_vis(cycles.size(), false);

  function<void(Cactus&)> dfs = [&](Cactus& t) {
    ull u = t.head;
    //assert(vis[u]);

    for (ull i : cycles_per_node[u]) if (!cycle_vis[i]) {
      cycle_vis[i] = true;
      t.cycles.push_back({});
      //assert(!cycles[i].empty());
      ull j = 0;
      while (cycles[i][j] != u) j++;
      //assert(cycles[i][j] == u);
      ull sz = cycles[i].size();
      fore(k, 1, sz) {
        ull v = cycles[i][(j + k) % sz];
        //assert(!vis[v]);
        vis[v] = true;
      }
      fore(k, 1, sz) {
        ull v = cycles[i][(j + k) % sz];
        t.cycles.back().push_back({v, {}, {}});
        dfs(t.cycles.back().back());
      }
    }

    for (ull v : adj[u]) {
      if (!vis[v]) {
        vis[v] = true;
        t.children.push_back({v, {}, {}});
        dfs(t.children.back());
      }
    }
  };

  Cactus ans = {0, {}, {}};
  vis[0] = true;
  dfs(ans);

  return ans;
}

