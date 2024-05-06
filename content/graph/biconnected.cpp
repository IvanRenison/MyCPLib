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
    for (auto [y, e] : ed[at]) if (e != par) {
      if (y == at) { // self loop
        ans.edges_comp[e] = ans.n_comps;
        ans.nodes_comp[at].insert(ans.n_comps);
        ans.n_comps++;
      } else if (num[y]) {
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
