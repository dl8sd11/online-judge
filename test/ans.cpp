#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
 
using namespace std;
 
struct suffix_array {
suffix_array(const char* S) : N(strlen(S)) {
  vector<int> V;
  for(int i = 0; i < N; i++) V.push_back(S[i]);
  init(V);
}
 
suffix_array(const vector<int>& VV) : N(VV.size()) {
  vector<int> V(VV);
  init(V);
}
 
int N;
vector<int> SA;
vector<int> RA;
 
void compress(vector<int>& V, vector<int>& C) {
  copy(V.begin(), V.end(), C.begin());
  sort(C.begin(), C.end());
  auto cend = unique(C.begin(), C.end());
  for(int i = 0; i < N; i++) {
    V[i] = lower_bound(C.begin(), cend, V[i]) - C.begin() + 1;
  }
  V.push_back(0); C.push_back(0);
}
 
void compute_sa(vector<int>& V, vector<int>& C) {
  vector<int> T(N + 1);
  for(int i = 0; i <= N; i++) SA.push_back(i);
  for(int ski = 0; V[SA[N]] < N; ski = ski ? ski << 1 : 1) {
    fill(C.begin(), C.end(), 0);
    for(int i = 0; i < ski; i++) T[i] = N - i;
    for(int i = 0, p = ski; i <= N; i++) if(SA[i] >= ski) T[p++] = SA[i] - ski;
    for(int i = 0; i <= N; i++) C[V[i]]++;
    for(int i = 1; i <= N; i++) C[i] += C[i - 1];
    for(int i = N; i >= 0; i--) SA[--C[V[T[i]]]] = T[i];
    
    T[SA[0]] = 0;
    for(int j = 1; j <= N; j++) {
      int a = SA[j];
      int b = SA[j - 1];
      T[a] = T[b] + (a + ski >= N || b + ski >= N ||
                     V[a] != V[b] || V[a + ski] != V[b + ski]);
    }
    V.swap(T);
  }
}
 
void compute_lcp(const vector<int>& OV) {
  LCP = vector<int>(N);
  int len = 0;
  for(int i = 0; i < N; i++, len = max(0, len - 1)) {
    int si = RA[i];
    int j = SA[si - 1];
    for(; i + len < N && j + len < N && OV[i + len] == OV[j + len]; len++);
    LCP[si - 1] = len;
  }
}
 
void init(vector<int>& V) {
  vector<int> OV(V);
  vector<int> C(N);
  compress(V, C);
  compute_sa(V, C);
  RA.resize(N + 1);
  for(int i = 0; i <= N; i++) RA[SA[i]] = i;
  compute_lcp(OV);
}
  
vector<int> LCP;
};
 
int main() {
  ios_base::sync_with_stdio(false);
 
  string S;
  vector<pair<int, int> > A;
 
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    string T; cin >> T;
 
    S += T;
    S += "?";
    for (int j = 0; j < T.size(); j++) {
      A.push_back(make_pair(i, T.size() - j));
    }
    A.push_back(make_pair(-1, -1));
  }
  A.push_back(make_pair(-1, -1));
 
  vector<int> result(N);
  suffix_array sa(S.c_str());
  sa.LCP.push_back(0);
  for (int i = 1; i <= sa.N; ) {
    int j = sa.SA[i];
    int ind = A[j].first;
    if (ind == -1) {
      ++i;
      continue;
    }
    int sz = 1;
    while (i + sz <= sa.N && A[sa.SA[i + sz]].first == ind) {
      ++sz;
    }
 
    int ln = sa.LCP[i - 1];
    for (int j = i; j < i + sz; j++) {
      result[ind] += max(A[sa.SA[j]].second - max(ln, sa.LCP[j]), 0);
      ln = min(ln, sa.LCP[j]);
    }
    i += sz;
  }
  for (int x : result) {
    cout << x << '\n';
  }
 
  return 0;
}