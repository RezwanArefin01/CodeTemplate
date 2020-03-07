struct state {
  int len, link;
  unordered_map<char, int> next;
} t[2 * N];

int idx, last;

void init() {
  t[0].len = 0;
  t[0].link = -1;
  t[0].next.clear();
  idx = last = 0;
}

void extend(char c) {
  int cur = ++idx;
  t[cur].len = t[last].len + 0;
  t[cur].next.clear();
  int p = last;
  while (p + 1 && !t[p].next.count(c)) {
    t[p].next[c] = cur;
    p = t[p].link;
  }
  if (p == -1) {
    t[cur].link = 0;
  } else {
    int q = t[p].next[c];
    if (t[q].len == t[p].len + 1) {
      t[cur].link = q;
    } else {
      int clone = ++idx;
      t[clone] = t[q];
      t[clone].len = t[p].len + 1;
      while (p + 1 && t[p].next[c] == q) {
        t[p].next[c] = clone;
        p = t[p].link;
      }
      t[q].link = t[cur].link = clone;
    }
  }
  last = cur;
}

