#pragma once

#include <IncludeTemplate.hpp>

struct Trie {
  struct Node {
    // amount of words that end in this node
    uint countEnds;
    // amount of words that pass through this node
    uint countPass;
    map<char, uint> children; // Use vector for better performance if alphabet is small
  };

  vector<Node> nodes;

  Trie() : nodes(1) {}

  // Inserts key into trie
  void insert(const string& key) {
    uint i = 0;
    for (char c : key) {
      nodes[i].countPass++;
      if (nodes[i].children.count(c) == 0) {
        nodes[i].children[c] = nodes.size();
        nodes.push_back(Node());
      }
      i = nodes[i].children[c];
    }
    nodes[i].countEnds++;
  }

  // Returns (countEnds, countPass) of key
  uu search(const string& key) {
    uint i = 0;
    for (char c : key) {
      if (nodes[i].children.count(c) == 0) {
        return {0, 0};
      }
      i = nodes[i].children[c];
    }
    return {nodes[i].countEnds, nodes[i].countPass};
  }
};
