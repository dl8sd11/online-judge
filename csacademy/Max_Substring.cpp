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
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll MAXN = 


struct SuffixArray {
    ll n;
    string s;
    vector<ll> x,r,t,lcp;
    SuffixArray(const string str) : s(str), n(SZ(str)), x(n), r(n), t(n), lcp(n) {
        REP (i,n) {
            r[x[i] = i] = s[i];
        }
        for (ll h=1; t[n-1] != n-1; h*=2) {
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
        build_lcp();
    }

    ll operator [] (ll idx) {
        return x[idx];
    }

    void build_lcp() {
        for (ll i = 0; i < n; i++) {
            r[x[i]] = i;
        }
        for (ll i = 0,p = 0; i < n; i++) {
            if (r[i] == 0) {
                lcp[0] = 0;
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


string str;

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> str;
    SuffixArray sa(str);

    debug(sa.x);
    debug(sa.lcp);

    pair<ll,string> ans;
    ans = {1,str};
    ll len = 1,lcp = INF;
    REP (i,SZ(str)) {
        if (sa.lcp[i] == 0) {
            len = 1,lcp = INF;
        } else {
            len++;
            lcp = min(lcp,sa.lcp[i]);
            string ns = str.substr(sa.x[i],lcp);
            if (len > ans.X) {
                ans.X = len;
                ans.Y = ns;
            } else if (len == ans.X) {
                if (lcp > SZ(ans.Y)) {
                    ans.Y = ns;
                } else if (lcp == SZ(ans.Y)) {
                    if (ans.Y > ns) {
                        ans.Y = ns;
                    }
                }
            }
        }
    }

    cout << ans.Y << endl;
}
