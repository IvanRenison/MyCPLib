#pragma once

#include <IncludeTemplate.hpp>

/* General perfect two players game in a directed graph that can have cycles
 * Who can not move loses
 * Returns a vector with the result for the player that starts in that position, with:
 *   1 if the player wins
 *   0 if it is a draw
 *  -1 if the player loses
 */
vi general_game(ull n, vii& edges) {
  vector<vu> adj_back(n);
  vu deg(n);

  for (auto [u, v] : edges) {
    adj_back[v].push_back(u);
    deg[u]++;
  }

  vi ans(n, 0);
  vu s;
  fore(u, 0, n) {
    if (deg[u] == 0) {
      s.push_back(u);
      ans[u] = 1; // Winner
    }
  }

  while (!s.empty()) {
    ull u = s.back();
    s.pop_back();

    if (ans[u] == -1) { // u is loser
      for (ull v : adj_back[u]) {
        if (ans[v] == 0) {
          ans[v] = 1; // Winner
          s.push_back(v);
        }
      }
    } else { // u is winner
      // assert(ans[u] == 1);
      for (ull v : adj_back[u]) {
        if (ans[v] == 0) {
          deg[v]--;
          if (deg[v] == 0) {
            ans[v] = -1; // Loser
            s.push_back(v);
          }
        }
      }
    }
  }

  return ans;
}
