#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100003;
int n,q;
int seg[MAXN*2],tag[MAXN*2];


void build() {
  for (int i=n-1;i>0;i--) {
    seg[i] = max(seg[i<<1],seg[i<<1|1]);
  }
}

inline void pull(int pos) {
  for (pos>>=1;pos>0;pos>>=1) {
    seg[pos] = max(seg[pos<<1],seg[pos<<1|1]) + tag[pos];
  }
}

inline void apply(int pos,int val) {
  seg[pos] += val;
  if (pos < n) {
    tag[pos] += val;
  }
}

inline void add(int l,int r,int data) {
  l += n,r += n;
  int l0 = l,r0 = r;
  for (;l<r;l>>=1,r>>=1) {
    if (l&1) {
      apply(l++,data);
    }
    if (r&1) {
      apply(--r,data);
    }
  }
  pull(l0);
  pull(r0);
}

inline void push(int pos) {
  int h = sizeof(int) * 8 - __builtin_clz(n);
  for (int s=h;s>0;s--) {
    int i = pos >> s;
    apply(i<<1,tag[i]);
    apply(i<<1|1,tag[i]);
    tag[i] = 0;
  }
}
inline int query(int l,int r) {
  l += n,r += n;
  push(l);
  push(r);
  int res = 0;
  for (;l<r;l>>=1,r>>=1) {
    if (l&1) {
      res = max(res,seg[l++]);
    }
    if (r&1) {
      res = max(res,seg[--r]);
    }
  }

  return res;
}

int main () {
  cin >> n >> q;
  for (int i = 0;i<n;i++) {
    cin >>seg[i+n];
  }

  build();

  while (q--) {
    int cmd,l,r,x;
    cin >> cmd >> l >> r;
    if (cmd == 1) {
      cin >> x;
      add(l-1,r,x);
    } else if (cmd == 2) {
      cout << query(l-1,r) << endl;
    }
  }

}