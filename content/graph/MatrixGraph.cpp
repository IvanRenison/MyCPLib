#pragma once

#include <IncludeTemplate.hpp>

template <typename T>
struct Matrix {
  ull n, m;
  vector<T> data;

  Matrix(ull n, ull m) {
    this->n = n, this->m = m;
    data = vector<T>(n * m);
  }

  Matrix(ull n, ull m, T val) {
    this->n = n, this->m = m;
    data = vector<T>(n * m, val);
  }

  Matrix(istream& in) {
    in >> n >> m;
    data = vector<T>(n * m);
    fore(i, 0, n) {
      fore(j, 0, m) {
        in >> this[{i, j}];
      }
    }
  }

  vuu neighbors(ull i, ull j) {
    vuu ans;
    if (i > 0) {
      ans.push_back({i - 1, j});
    }
    if (i < n - 1) {
      ans.push_back({i + 1, j});
    }
    if (j > 0) {
      ans.push_back({i, j - 1});
    }
    if (j < m - 1) {
      ans.push_back({i, j + 1});
    }
    return ans;
  }

  T operator[](uu p) const {
    auto [i, j] = p;
    return data[j * n + i];
  }

  void assign(ull i, ull j, T val) {
    data[j * n + i] = val;
  }

  template <T>
    requires(!is_same<T, bool>::value)
  T& operator[](uu p) {
    auto [i, j] = p;
    return data[j * n + i];
  }
};

/* Make dfs from (i, j) and return all the positions visited */
vuu dfs(Matrix<bool> mat, ull i, ull j) {
  Matrix<bool> visited(mat.n, mat.m, false);
  visited.assign(i, j, true);

  vuu ans = {{i, j}};
  vuu s = {{i, j}};

  while (!s.empty()) {
    auto [ni, nj] = s.back();
    s.pop_back();

    for (auto [i, j] : mat.neighbors(ni, nj)) {
      if (!visited[{i, j}] && mat[{i, j}]) {
        visited.assign(i, j, true);
        ans.push_back({i, j});
        s.push_back({i, j});
      }
    }
  }

  return ans;
}
