#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define X first
#define Y second
#define eb emplace_back
#define MEM(i,a) memset(i, (a), sizeof(i))
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream& __printRng (ostream& os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg; it!=ed; it++) {
        if (it==bg) os << *it;
        else os << "," << *it;
    }
    return os << "}";
}
template<typename T> ostream& operator << (ostream& os, const vector<T> &v) {return __printRng(os, ALL(v));}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

int n;
string str;
vector<int> mat;
vector<int> w, b;

bool in (int x, int y) {
    int mx = mat[x], my = mat[y];
    int l1 = b[x], r1 = w[mx];
    if (l1 > r1) swap(l1, r1);
    int l2 = b[y], r2 = w[my];
    if (l2 > r2) swap(l2, r2);
    return (l1 < l2 && l2 < r1 && r1 < r2) ||
        (l2 < l1 && l1 < r2 && r2 < r1);

}

int check () {
    int res = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (in(i,j)) {
                res++;
            }
        }
    }
    return res;
}

int main () {

    IOS();
    cin >> n;
    cin >> str;
    mat.resize(n);
    for (int i=0; i<n*2; i++) {
        if (str[i] == 'W') w.eb(i);
        else b.eb(i);
    }
    iota(ALL(mat), 0);

    reverse(ALL(mat));

    cout << check() << endl;
}
