#pragma GCC optimize("Ofast,fast-math,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#include<cstdio>
#include<algorithm>
#include<vector>
#include<utility>
#include<iostream>
using namespace std;
typedef int64_t lld;

const int S = 1<<24; // buffer size
char buf[S], *p = buf, *q = buf;
inline char readchar() {
	if(p == q && (q = (p=buf)+fread(buf,1,S,stdin)) == buf) return EOF;
	return *p++;
}

inline void input(int& x) {
	int c = getchar();
	while('0' > c || c > '9') c = readchar();
	while('0' <= c && c <= '9') x = (x*10) + (c^'0'), c = readchar();
}

const int MAXN = 1000000, INT_MAX = 2147483647, MAXQ = 1000000;
int a[MAXN]={}, mn[MAXN], mx[MAXN], lft[MAXN], mnl = 0, mnr = 0, mxl = 0, mxr = 0;
lld ans[MAXQ] = {};
struct Node {
  int min = INT_MAX, smin = INT_MAX, min_num = 1;
  lld sums = 0;
};
vector<Node> sgt;
inline void up(int i){
  if(sgt[i<<1].min == sgt[i<<1|1].min)sgt[i].smin = min(sgt[i<<1].smin, sgt[i<<1|1].smin);
  else sgt[i].smin = max(sgt[i<<1].min, sgt[i<<1|1].min);
  sgt[i].min_num = 1;
  if(sgt[i<<1].min == sgt[i].min)sgt[i].min_num += sgt[i<<1].min_num;
  if(sgt[i<<1|1].min == sgt[i].min)sgt[i].min_num += sgt[i<<1|1].min_num;
  sgt[i].sums = sgt[i<<1].sums + sgt[i<<1|1].sums;
}
void update(int ll, int rr, int x, int i, int l, int r){
  if(ll > r || rr < l)return;
  if(sgt[i].min >= x)return;
  sgt[i].sums += sgt[i].min_num*(lld)(x - sgt[i].min);
  sgt[i].min = x;
  if(sgt[i].smin > x)return;
  update(ll, rr, x, i<<1, l, l+r>>1);
  update(ll, rr, x, i<<1|1, (l+r>>1)+1, r);
  up(i);
}
void build(int i, int l, int r){
  if(l == r)sgt[i].min = sgt[i].sums = lft[l];
  else
    build(i<<1, l, l+r>>1),
    build(i<<1|1, (l+r>>1)+1, r),
    sgt[i].min = min(sgt[i<<1].min, sgt[i<<1|1].min),
    up(i);
}
lld query(int ll, int rr, int i, int l, int r){
  if(ll > r || rr < l)return 0;
  if(ll <= l && rr >= r)return sgt[i].sums;
  return query(ll, rr, i<<1, l, l+r>>1);
      + query(ll, rr, i<<1|1, (l+r>>1)+1, r);
}
vector<pair<int, int>> qs[MAXN];
signed main(){
  int n = 0, k = 0;
  input(n); input(k);
  sgt.resize(n<<2);
  for(int l = 0, r = 0; r < n; r++){
    input(a[r]);
    while(mnl != mnr && a[mn[mnr-1]] >= a[r])mnr--; mn[mnr++] = r;
    while(mxl != mxr && a[mx[mxr-1]] <= a[r])mxr--; mx[mxr++] = r;
    while(a[mx[mxl]]-a[mn[mnl]] > k){
      l = (mx[mxl]<mn[mnl]?mx[mxl]:mn[mnl])+1;
      if(mx[mxl] < l)mxl++;
      if(mn[mnl] < l)mnl++;
    }
    lft[r] = l;
  }
  build(1, 0, n-1);// cout << sgt[1].sums << endl;
  int q = 1;
  input(q);
  for(int i = 0; i < q; i++){
    int l, r;
    input(l), input(r); l--; r--;
    qs[l].push_back({r, i});
  }//*/
  //qs[0].push_back({n-1, 0});

  for(int i = 0; i < n; i++){
    //cout << lft[i] << " ";
    if(qs[i].empty())continue;
    update(0, n-1, i, 1, 0, n-1);
    for(auto p: qs[i])
      ans[p.second] = (lld)(p.first+i)*(p.first-i+1)/2 + p.first-i+1 - query(i, p.first, 1, 0, n-1);
  }
  for(int i = 0; i < q; i++)
    printf("%lld\n", (long long)ans[i]);
}
