#include <IncludeTemplate.hpp>

struct BCC_ans {
  ull n_comps; // number of biconnected components
  vu edges_comp; // component of each edge or inf if bridge
  vector<set<ull>> nodes_comp; // component of each node

  BCC_ans(ull n, ull m) : n_comps(0), edges_comp(m, inf), nodes_comp(n) {}
};

BCC_ans BCC(ull n, const vuu& edges) {
  ull m = edges.size();
  vu num(n), st;
  vector<vector<uu>> ed(n);
  ull Time = 0;

  ull eid = 0;
  for (auto [a, b] : edges) {
    ed[a].emplace_back(b, eid);
    ed[b].emplace_back(a, eid++);
  }

  BCC_ans ans(n, m);

  function<ull(ull, ull)> dfs = [&](ull at, ull par){
    ull me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at]) if (pa.second != par) {
      tie(y, e) = pa;
      if (num[y]) {
        top = min(top, num[y]);
        if (num[y] < me)
          st.push_back(e);
      } else {
        ull si = st.size();
        ull up = dfs(y, e);
        top = min(top, up);
        if (up == me) {
          st.push_back(e);
          {
            vu comp(st.begin() + si, st.end());
            for (ull e : comp) {
              ans.edges_comp[e] = ans.n_comps;
              auto [u, v] = edges[e];
              ans.nodes_comp[u].insert(ans.n_comps);
              ans.nodes_comp[v].insert(ans.n_comps);
            }
            ans.n_comps++;
          }
          st.resize(si);
        }
        else if (up < me) st.push_back(e);
        else { /* e is a bridge */ }
      }
    }
    return top;
  };

  fore(i, 0, n) if (!num[i]) {
    dfs(i, inf);
  }

  fore(u, 0, n) {
    if (ans.nodes_comp[u].empty()) {
      ans.nodes_comp[u].insert(ans.n_comps);
      ans.n_comps++;
    }
  }

  return ans;
};

BCC_ans BCC_multiedges(ull n, vuu edges) { // BCC for graphs with multiple edges and self loops
  ull m = edges.size();

  map<uu, vu> repeated_edges;
  vu self_loops;

  map<uu, ull> edges_map;
  fore(e, 0, m) {
    auto& [u, v] = edges[e];
    if (u == v) {
      self_loops.push_back(e);
    } else {
      if (u > v) {
        swap(u, v);
      }
      if (edges_map.count({u, v})) {
        repeated_edges[{u, v}].push_back(e);
      } else {
        edges_map[{u, v}] = e;
      }
    }
  }

  vuu edges_;
  vu edges_original_id;

  for (auto [uv, e] : edges_map) {
    edges_.push_back(uv);
    edges_original_id.push_back(e);
  }

  BCC_ans simp_ans = BCC(n, edges_);

  BCC_ans ans(n, m);
  ans.n_comps = simp_ans.n_comps;
  ans.nodes_comp = simp_ans.nodes_comp;

  fore(e_, 0, edges_.size()) {
    ull e = edges_original_id[e_];
    if (simp_ans.edges_comp[e_] != inf) {
      ans.edges_comp[e] = simp_ans.edges_comp[e_];
    }
  }

  for (auto& [uv, es] : repeated_edges) {
    auto [u, v] = uv;
    ull common_comp = inf;
    for (ull comp : ans.nodes_comp[u]) {
      if (ans.nodes_comp[v].count(comp)) {
        common_comp = comp;
        break;
      }
    }
    if (common_comp == inf) {
      common_comp = ans.n_comps;
      ans.n_comps++;
      for (ull e : es) {
        ans.edges_comp[e] = common_comp;
      }
      ans.edges_comp[edges_map[uv]] = common_comp;
    } else {
      for (ull e : es) {
        ans.edges_comp[e] = common_comp;
      }
    }
  }

  for (ull e : self_loops) {
    ans.edges_comp[e] = ans.n_comps;
    ans.nodes_comp[edges[e].first].insert(ans.n_comps);
    ans.n_comps++;
  }

  return ans;
}