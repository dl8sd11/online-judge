#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> ostream &operator << (ostream &os,pair<T,T> &v){return os<<"{"<<v.X<<","<<v.Y<<"}";}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

int t, n;
vector<pll> pts;
vector<pll> h;

pll operator - (const pll &a, const pll &b) {
    return {a.X-b.X, a.Y-b.Y};
}

ll area (const pll &a, const pll &b) {
    return abs(a.X * b.Y - a.Y * b.X);
}

ll operator % (const pll &a, const pll &b) {
    return a.X * b.Y - a.Y * b.X;
}

ll qar (pll a, pll b, pll c, pll d) {
    return area(b-d, a-d) + area(b-d, c-d);
}

void build_hull () {
    sort(ALL(pts));
    for (int i=0; i<SZ(pts); i++) {
        while (h.size() >= 2 && (pts[i]-h.back()) % (pts[i]-h[SZ(h)-2]) <= 0) {
            h.pop_back();
        }
        h.emplace_back(pts[i]);
    }

    int c = h.size();
    for (int i=SZ(pts)-2; i>=0; i--) {
        while (h.size() >= c+1 && (pts[i]-h.back()) % (pts[i]-h[SZ(h)-2]) <= 0) {
            h.pop_back();
        }
        h.emplace_back(pts[i]);
    }

    h.pop_back();
    debug(h);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        pts.clear();
        h.clear();

        cin >> n;
        REP (i, n) {
            int x, y;
            cin >> x >> y;
            pts.eb(x, y);
        }

        build_hull();

        ll ans = 0;

        if (h.size() <= 2) {
            ans = 0;
        } else if (h.size() == 3) {
            multiset<pll> np;
            for (auto v : pts) {
                np.insert(v);
            }
            np.erase(np.find(h[0]));
            np.erase(np.find(h[1]));
            np.erase(np.find(h[2]));

            debug(SZ(np));
            debug(np.begin()->first);
            for (auto v : np) {
                vector<ll> ta;
                ta.eb(area(h[0]-h[1], v-h[1]));
                ta.eb(area(h[2]-h[1], v-h[1]));
                ta.eb(area(h[2]-h[0], v-h[0]));
                sort(ALL(ta));
                ans = max(ans, ta[1]+ta[2]);
            }

            debug(ans);
        } else {
            int sz = SZ(h);


            for (int len=2; len<sz-1; len++) {
                int u = 0, d = len;
                REP (l, sz-len) {
                    int r = l + len;
                    pll bs = h[r] - h[l];
                    while (area(bs, h[(u+1)%sz]-h[l]) >= area(bs, h[u]-h[l])) {
//                        debug(l, r, u);
                        u++;
                        if (u >= sz) {
                            u -= sz;
                        }
                    }
                    while (area(bs, h[(d+1)%sz]-h[l]) >= area(bs, h[d]-h[l])) {
//                        debug(l, r, d);
                        d++;
                        if (d >= sz) {
                            d -= sz;
                        }
                    }

                    ans = max(ans, area(bs, h[d]-h[l]) + area(bs, h[u]-h[l]));

                }
            }
        }

        if (ans & 1) {
            cout << ans / 2 << ".5" << endl;
        } else {
            cout << ans/2 << endl;
        }
    }


}
