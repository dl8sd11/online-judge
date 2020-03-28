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
template<typename T> ostream &operator << (ostream &os,multiset<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 200005;
const ll MOD = 1000000007;
const int K = 502;


int t, n, q, a[MAXN], rk[MAXN], vn;
ll ans[MAXN];
vector<int> val;

struct DS {
    int sz[MAXN*2];
    ll seg[MAXN*2][3];

    void clr () {
        REP (i, n*2) {
            sz[i] = 0;
            REP (j, 3) {
                seg[i][j] = 0;
            }
        }
    }

    void add_sz (int x, int v) {
        sz[x+=vn]+=v;
        REP (i, 3) {
            seg[x][i] = (sz[x] >= i+1) ? val[x-vn] : 0;
        }
        for (; x>1; x>>=1) {
            sz[x>>1] = sz[x] + sz[x^1];
            REP (i, 3) {
                seg[x>>1][i] = seg[x][i] | seg[x^1][i];
            }
        }
    }

    int qry_sz (int l, int r) {
        int ret = 0;
        for (l+=vn, r+=vn; l<r; l>>=1, r>>=1) {
            if (l&1) {
                ret += sz[l++];
            }
            if (r&1) {
                ret += sz[--r];
            }
        }
        return ret;
    }

    array<ll,3> qry_f (int l, int r) {
        array<ll,3> ret = {0, 0, 0};
        for (l+=vn, r+=vn; l<r; l>>=1, r>>=1) {
            if (l&1) {
                REP (i, 3) {
                    ret[i] |= seg[l][i];
                }
                l++;
            }
            if (r&1) {
                --r;
                REP (i, 3) {
                    ret[i] |= seg[r][i];
                }
            }
        }
        return ret;
    }
} ds;

struct Query {
    int l, r, u, v, lid, qid;

    bool operator < (const Query &oth) const {
        if (lid != oth.lid) {
            return lid < oth.lid;
        } else {
            return (lid&1) ? r > oth.r : r < oth.r;
        }
    }
};
vector<Query> query;

#ifdef tmd
multiset<int> ms;
#endif // tmd

void init () {
    query.clear();
    val.clear();
    ds.clr();
    #ifdef tmd
    ms.clear();
    #endif // tmd
}




void add (int x) {
    ds.add_sz(rk[x], 1);

    #ifdef tmd
    ms.insert(a[x]);
    #endif // tmd
}

void sub (int x) {
    ds.add_sz(rk[x], -1);

    #ifdef tmd
    ms.erase(ms.find(a[x]));
    #endif // tmd
}

ll qry (int l, int r) {
    int LL = -1, LR = vn;
    while (LL < LR - 1) {
        int LM = (LL + LR) >> 1;
        if (ds.qry_sz(0, LM) >= l-1) {
            LR = LM;
        } else {
            LL = LM;
        }
    }

    int L = LR;

    int RL = -1, RR = vn;
    while (RL < RR - 1) {
        int RM = (RL + RR) >> 1;
        if (ds.qry_sz(0, RM+1) <= r) {
            RL = RM;
        } else {
            RR = RM;
        }
    }

    int R = RL;
    array<ll,3> res = ds.qry_f(L, R + 1);

    int lrem = ds.qry_sz(0, L)-l+1, rrem = r - ds.qry_sz(0, R+1);


    if (LL == RR) {
        lrem = r-l+1;
        rrem = 0;
    }
//    debug(LL, LR, RL, RR, lrem, rrem);
    REP (i, 3) {
        if (lrem >= i+1) {
            res[i] |= val[LL];
        }
        if (rrem >= i+1) {
            res[i] |= val[RR];
        }
    }

    #ifdef tmd

    map<int,int> cnt;
    vector<int> vec;
    for (auto v : ms) {
        vec.eb(v);
    }

    for (int i=l-1; i<r; i++) {
        cnt[vec[i]]++;
    }

    array<ll,3> tmp = {0, 0, 0};
    for (auto p : cnt) {
        REP (j, 3) {
            if (p.Y >= j+1) {
                tmp[j] |= p.X;
            }
        }
    }

    assert(tmp == res);
    #endif // tmd

    return res[0] + res[1] + res[2];

}
/*
1
10 4
0 0 1 1 2 2 3 3 4 4
1 10 3 8
1 10 3 7
1 10 4 8
1 10 4 7
*/
//#define test

/*
1
4 1
2 6 6 6
2 4 2 2
*/
/*********************GoodLuck***********************/
signed main () {
    IOS();
    srand(279936);

    cin >> t;
    while (t--) {

        #ifdef test
        n = rand()%10+1, q = 10;
        #else
        cin >> n >> q;
        #endif // test
        init();

        REP (i, n) {
            #ifdef test
            a[i] = rand()%10;
            #else
            cin >> a[i];
            #endif // test
            val.eb(a[i]);
        }
//        pary(a,a+n);

        REP (i, q) {
            int l, r, u, v;
            #ifdef test
            l = rand() % n;
            r = rand() % n;
            if (l > r) {
                swap(l, r);
            }

            u = rand() % (r-l+1) + 1;
            v = rand() % (r-l+1) + 1;
            if (u > v) {
                swap(u, v);
            }
            #else
            cin >> l >> r >> u >> v;
            assert(1 <= l && l <= r && r <= n);
            assert(1 <= u && u <= v && v <= r-l+1);
            l--, r--;
            #endif // test
            query.push_back({l, r, u, v, l/K, i});
        }

        sort(ALL(val));
        val.resize(unique(ALL(val))-val.begin());
        vn = SZ(val);
//        debug(val);

        REP (i, n) {
            rk[i] = lower_bound(ALL(val), a[i]) - val.begin();
        }

        sort(ALL(query));
        int l = 0, r = -1;
        for (Query Q : query) {
            while (Q.r > r) {
                add(++r);
            }
            while (Q.l < l) {
                add(--l);
            }

            while (Q.r < r) {
                sub(r--);
            }
            while (Q.l > l) {
                sub(l++);
            }

            #ifdef tmd
            multiset<int> ck;
            for (int i=Q.l; i<=Q.r; i++) {
                ck.insert(a[i]);
            }
            assert(ck == ms);

            #endif // tmd

//            debug(ms, Q.l, Q.r, Q.u, Q.v);

            ans[Q.qid] = qry(Q.u, Q.v);
        }

        REP (i, q) {
            #ifndef test
            cout << ans[i] << endl;
            #endif // tmd
        }
    }
}
