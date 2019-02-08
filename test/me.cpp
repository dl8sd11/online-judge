#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;

struct SuffixArray {
    ll n;
    string s;
    vector<ll> x,r,t,lcp;
    SuffixArray(const string str) : s(str),n(SZ(str)),lcp(n), x(n), r(n), t(n) {
        for (ll i=0; i < n; i++) {
            r[x[i] = i] = s[i];
        }
        for (ll h=1; t[n-1] != n-1; h *= 2) {
            auto cmp = [&](ll i,ll j) {
                if (r[i] != r[j]) {
                    return r[i] < r[j];
                } else {
                    return i+h < n && j+h < n ? r[i+h] < r[j+h] : i > j;
                }
            };
            sort(ALL(x),cmp);
            for (ll i=0; i+1 < n; i++) {
                t[i+1] = t[i] + cmp(x[i],x[i+1]);
            }
            for (ll i=0; i < n; i++) {
                r[x[i]] = t[i];
            }
        }                    
    }
    ll operator [] (ll idx) {
        return x[idx];
    }

    void build_lcp() {
        for (ll i = 0,p = 0; i < n; i++) {
            if (r[i] == 0) {
                lcp[r[i]] = 0;
            } else {
                ll j = x[r[i]-1];
                if (p > 0) {
                    p--;
                }
                while (s[i+p] == s[j+p]) {
                    p++;
                }
                lcp[r[i]] = p;
            }
        }
    }

};
ll L[MAXN],R[MAXN],G[MAXN],gid,st[MAXN],ans[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    ll n;
    string name[MAXN],t;

// #ifndef tmd
//     freopen("standingout.in","r",stdin);
//     freopen ("standingout.out","w",stdout);
// #endif
    cin >> n;
    REP (i,n) {
        cin >> name[i];
        t += name[i] + char(123);
        st[i] = gid;
        REP (j,SZ(name[i])) {
            G[gid++] = i;
        }
        G[gid++] = -1;
    }
    debug(t);
    pary(G,G+SZ(t));
    
    SuffixArray sa(t);
    sa.build_lcp();

    debug(sa.lcp);
    REP (i,sa.n) {
        debug(t.substr(sa[i]));
    }
    REP (i,sa.n) {
        if (i == 0) {
            L[sa[i]] = 0;
        } else {
            ll idx = sa[i];
            ll cp = min(SZ(name[G[idx]])-idx+st[G[idx]],sa.lcp[i]);
            if (G[idx] != G[sa[i-1]]) {
                L[idx] = cp;
            } else {
                L[idx] = min(cp,L[sa[i-1]]);
            }
        }
    }

    RREP(i,sa.n-1) {
        ll idx = sa[i];
        if (i == sa.n - 1) {
            R[idx] = 0;
        } else {
            debug(SZ(name[G[idx]])-idx+st[G[idx]],sa.lcp[i+1]);
            R[idx] = min(SZ(name[G[idx]])-idx+st[G[idx]],sa.lcp[i+1]);
        }
    }
    // REP (i,sa.n) {
    //     if (sa.r[i] == 0) {
    //         L[i] = 0;
    //     } else {
    //         ll cur = sa.r[i]; // rank of the suffix
    //     }
    // }

    // RREP(i,sa.n-1) {
    //     if (sa.r[i] == sa.n - 1) {
    //         R[i] = 0;
    //     } else {
    //         ll cur = sa.r[i];
    //         R[i] = min(SZ(name[G[i]])-i+st[G[i]],sa.lcp[cur+1]);
    //     }
    // }

    pary(L,L+sa.n);
    pary(R,R+sa.n);

    REP (i,sa.n) {
        if (G[i] != -1) {
            ans[G[i]] += SZ(name[G[i]])-i+st[G[i]]-max(L[i],R[i]);
        }
    }

    REP (i,n) {
        cout << ans[i] << endl;
    }
    return 0;
}
