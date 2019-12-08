#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("03","unroll-loops")
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define MEM(a,b) memset(a,(b),sizeof(a))
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d: (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
template<typename T> ostream &operator << (ostream &os, const pair<T,T> &p){return os<<"("<<p.first<<","<<p.second<<")";}
template<typename IT> ostream &_printRng(ostream &os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg; it!=ed; it++) {
        os << (it==bg?"":",") << *it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os, const vector<T> &vec) {return _printRng(os, vec.begin(),vec.end());}
template<typename IT> void pary (IT bg, IT ed) {_printRng(cerr,bg,ed);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, q, w;
vector<int> a;

namespace N {
int solve () {
    vector<int> dt = a;
    sort(ALL(dt));


    int L = (n+1)/2-1, R = n;
    while (L < R - 1) {
        int M = (L + R) >> 1;

        int hd = n - M;
        bool valid = true;
        for (int i=0; i<M; i++) {
            if (hd-i-1 >= 0 && dt[hd+i]+dt[hd-i-1]>w) {
                valid = false;
            }
        }

        if (valid) {
            R = M;
        } else {
            L = M;
        }

    }

    return R;
}
}

namespace W {
    const int MAXC = 202;
    int cnt[MAXC+3];
    int c[MAXC];

    int solve () {
        int L = (n+1)/2-1, R = n;
        while (L < R - 1) {
            int M = (L + R) >> 1;

            int rptr = MAXC, sum = 0;
            while (sum<M && rptr >= 0) {
                rptr--;
                sum += cnt[rptr];
            }

            int l = sum - M, r = cnt[rptr]-l;
            int lptr = rptr;


            while (rptr < MAXC && lptr > 0) {
                if (l < r) {
                    if (l == 0) {
                        l = lptr ? cnt[--lptr] : 0;
                    } else if (lptr+rptr>w) {
                        L = M;
                        break;
                    } else {
                        r -= l;
                        l = lptr ? cnt[--lptr] : 0;
                    }
                } else if (l > r) {
                    if (r == 0) {
                        r = cnt[++rptr];
                    } else if (lptr+rptr>w) {
                        L = M;
                        break;
                    } else {
                        l -= r;
                        r = cnt[++rptr];
                    }
                } else {
                    if (lptr+rptr>w) {
                        L = M;
                        break;
                    } else {
                        r = cnt[++rptr];
                        l = lptr ? cnt[--lptr] : 0;
                    }
                }
            }

            if (lptr <= 0) {
                R = M;
            } else {
                L = M;
            }

        }

        return R;
    }
}

int main () {
    IOS();

    cin >> n >> q >> w;

    a.resize(n);
    REP (i, n) {
#ifdef tmd
        a[i] = rand() % (w- 1) + 1;
#else
        cin >> a[i];
#endif // tmd

        if (w <= 200) {
            W::cnt[a[i]]++;
        }
    }

    if (w <= 200) {
        cout << W::solve() << endl;
    } else {
        cout << N::solve() << endl;
    }
    while (q--) {
        int x, y;

#ifdef tmd
        x = rand() % n + 1;
        y = rand() % (w- 1) + 1;
#else
        cin >> x >> y;
#endif // tmd
        x--;

        if (w <= 200) {
            W::cnt[a[x]] --;
        }
        a[x] = y;
        if (w <= 200) {
            W::cnt[a[x]] ++;
        }
        if (w <= 200) {
            cout << W::solve() << endl;
        } else {
            cout << N::solve() << endl;
        }

    }
}
/*
200000 200000 200

5 4 10
8 8 1 3 6
3 10
3 3
1 1
5 10
*/
