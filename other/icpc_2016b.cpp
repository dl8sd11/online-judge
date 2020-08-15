#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
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
template<typename T> ostream &operator << (ostream &os,pair<T,T> &v){return os<<"("<<v.X<<","<<v.Y<<")";}
template<typename T> ostream &operator << (ostream &os,const array<T,3> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

void err () {
    cout << "syntax error" << endl;
    exit(0);
}

void check (vector<pii> &vec) {
    sort(ALL(vec));
    int mx = -MOD;
    for (auto p : vec) {
        if (mx > p.X) {
            err();
        }
        mx = max(mx, p.Y);
    }
}
/*********************GoodLuck***********************/
signed main () {
    IOS();

    int n;
    cin >> n;
    vector<pii> pts(n*2);
    for (int i=0; i<n*2; i++) {
        cin >> pts[i].X >> pts[i].Y;
    }
    vector<int> id(n*2);
    iota(ALL(id), 0);

    sort(ALL(id), [&](int i, int j) {
        return pts[i] < pts[j];
    });

    set<pii> stk;

    vector<pii> mat;
    for (int v : id) {
        if (v < n) {
            stk.emplace(pts[v].Y, v);
        } else {
            auto ptr = stk.upper_bound(pii(pts[v].Y, MOD));
            if (stk.empty() || ptr == stk.begin()) {
                err();
            } else {
                mat.eb(prev(ptr)->Y, v);
                stk.erase(prev(ptr));
            }
        }
    }

    map<int,vector<pii> > hori, vert;
    vector<array<int,3> > query; // {x,u,d} {x,-1,y} {x,MOD,y}
    for (auto p : mat) {
        int a, b, c, d;
        tie(a,b) = pts[p.X];
        tie(c,d) = pts[p.Y];
        int xa = a;
        int xc = c;
        int xb = b;
        int xd = d;


        hori[xa].eb(xb, xd);
        if (xa != xc) {
            hori[xc].eb(xb, xd);
            query.push_back({a, MOD, b});
            query.push_back({c, -1, b});

            if (b != d) {
                query.push_back({a, MOD, d});
                query.push_back({c, -1, d});
            }
        }
        vert[xb].eb(xa, xc);
        if (xd != xb) {
            vert[xd].eb(xa, xc);
            query.push_back({a, b, d});

            if (a != c) {
                query.push_back({c, b, d});
            }
        }

    }
    

    debug("built");

    for (auto &v : hori) {
        debug(v.Y);
        check(v.Y);
    }
    for (auto &v : vert) {
        debug(v.Y);
        check(v.Y);
    }

    sort(ALL(query));
    debug(query);

    set<int> pos;
    for (auto qry : query) {
        debug(qry);
        if (qry[1] == -1) {
            pos.erase(qry[2]);
        } else if (qry[1] == MOD) {
            if (pos.count(qry[2])) {
                err();
            }
            pos.emplace(qry[2]);
        } else {
            auto ptr = pos.upper_bound(qry[1]);
            if (ptr != pos.end() &&  ( *ptr ) < qry[2]) {
                err();
            }
        }
    }

    sort(ALL(mat));
    for (auto p : mat) {
        cout << p.Y + 1 - n << endl;
        //cout << "(" << pts[p.X] << "," << pts[p.Y] << ")," <<endl;
    }
}

