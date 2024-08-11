#pragma once

#include <IncludeTemplate.hpp>

/* Prufer Code to Tree
 * Complexity: O(V log V)
 */
vuu pruferCodeToTree(const vu& pruferCode) {
	// Stores number count of nodes in the prufer code
	unordered_map<ull, ull> nodeCount;

	// Set of integers absent in prufer code. They are the leaves
	set<ull> leaves;

	ull len = pruferCode.size();
	ull node = len + 2;

	// Count frequency of nodes
	fore(i, 0, len) {
		ull t = pruferCode[i];
		nodeCount[t]++;
	}

	// Find the absent nodes
	fore(i, 1, node + 1) {
		if (nodeCount.find(i) == nodeCount.end()) leaves.insert(i);
	}

	vuu edges;
	/* Connect Edges */
	fore(i, 0, len) {
		ull a = pruferCode[i]; // First node

		//Find the smallest number which is not present in prufer code now
		ull b = *leaves.begin(); // the leaf

		edges.push_back({a, b}); // Edge of the tree

		leaves.erase(b); // Remove from absent list
		nodeCount[a]--; // Remove from prufer code
		if (nodeCount[a] == 0) leaves.insert(a); // If a becomes absent
	}

	// The final edge
	edges.push_back({*leaves.begin(), *leaves.rbegin()});
	return edges;
}

vuu genRandomTree(ull n) {
	vu pruferCode;
	fore(i, 0, n - 2) {
		pruferCode.push_back(rand() % (n - 1) + 1);
	}
	auto edges = pruferCodeToTree(pruferCode);
	for (auto &[u, v] : edges) u--, v--;
	return edges;
}

