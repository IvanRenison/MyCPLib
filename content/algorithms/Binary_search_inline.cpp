// l  → lower, r → upper
while (l + 1 < r) {
  ull m = (l + r) / 2;
  if (f(m)) {
    r = m;
  } else {
    l = m;
  }
}

ull ans = l;