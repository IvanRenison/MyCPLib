#pragma once

#include <IncludeTemplate.hpp>

// source: https://www.geeksforgeeks.org/inversion-count-in-array-using-merge-sort/

// This function merges two sorted subarrays arr[l..m] and arr[m+1..r]
// and also counts inversions in the whole subarray arr[l..r]
ull countAndMerge(vector<ull>& arr, ull l, ull m, ull r) {

  // Counts in two subarrays
  ull n1 = m - l + 1, n2 = r - m;

  // Set up two vectors for left and right halves
  vector<ull> left(n1), right(n2);
  for (ull i = 0; i < n1; i++)
    left[i] = arr[i + l];
  for (ull j = 0; j < n2; j++)
    right[j] = arr[m + 1 + j];

  // Initialize inversion count (or result) and merge two halves
  ull res = 0;
  ull i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {

    // No increment in inversion count if left[] has a
    // smaller or equal element
    if (left[i] <= right[j])
      arr[k++] = left[i++];

    // If right is smaller, then it is smaller than n1-i
      // elements because left[] is sorted
    else {
      arr[k++] = right[j++];
      res += (n1 - i);
    }
  }

  // Merge remaining elements
  while (i < n1)
    arr[k++] = left[i++];
  while (j < n2)
    arr[k++] = right[j++];

  return res;
}

// Function to count inversions in the array
ull countInv(vector<ull>& arr, ull l, ull r){
  ull res = 0;
  if (l < r) {
    ull m = (r + l) / 2;

    // Recursively count inversions in the left and
    // right halves
    res += countInv(arr, l, m);
    res += countInv(arr, m + 1, r);

    // Count inversions such that greater element is in
      // the left half and smaller in the right half
    res += countAndMerge(arr, l, m, r);
  }
  return res;
}

ull inversionCount(vector<ull> arr) {
  ull n = arr.size();
  return countInv(arr, 0, n-1);
}