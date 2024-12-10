#pragma once

#include <IncludeTemplate.hpp>

#include <TreeHashing.cpp>

bool rooted_tree_iso(vector<vu>& adj0, vector<vu>& adj1, ull root0 = 0, ull root1 = 0) {
  TreeHash th0(adj0, root0);
  TreeHash th1(adj1, root1);
  return th0.hashes[root0] == th1.hashes[root1];
}

// For unrooted tree isomorphism root at centroids
// (or if you can do quadratic time compare all roots)
