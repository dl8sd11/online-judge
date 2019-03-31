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
const ll MAXN = 200001;

ll n,ban[MAXN];
string str;

struct SuffixArray {
    ll len;
    vector<ll> sa,rk,lcp;
    SuffixArray(const string s) : len(SZ(s)), sa(len), rk(len), lcp(len) {
        vector<ll> t(len);
        debug(s);
        REP (i,len) {
            rk[sa[i]=i] = s[i];
        }
        for (ll h=1;t[len-1]!=len-1;h*=2) {
            debug(h);
            auto cmp = [&](ll i,ll j) {
                if (rk[i] != rk[j]) {
                    return rk[i] < rk[j];
                } else {
                    return (i+h < len && j+h < len) ? rk[i+h] < rk[j+h] : i > j;
                }
            };
            sort(ALL(sa),cmp);
            debug(sa);
            for (ll i=0;i<len-1;i++) {
                t[i+1] = t[i] + cmp(sa[i],sa[i+1]);
            }
            for (ll i=0;i<len;i++) {
                rk[sa[i]] = t[i];
            }
        }
        if (len == 1) {
            rk[0] = 0;
        }
        ll sum = 0;
        REP (i,len) {
            if (rk[i] == 0) {
                lcp[0] = 0;
            } else {
                if (sum > 0) {
                    sum--;
                }
                while (s[i+sum] == s[sa[rk[i]-1]+sum]) {
                    sum++;
                }
                lcp[rk[i]] = sum;
            }
        }
        
    }

    ll operator[](ll idx) {
        return sa[idx];
    }
};
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    cin >> str;
    reverse(ALL(str));
    REP (i,n) {
        char c;
        cin >> c;
        ban[i] = (c == '1');
    }
    reverse(ban,ban+n);

    SuffixArray sa(str);

    vector<ll> hei;
    ll mn = INF;
    ll ans = 0;

    debug(sa.lcp);
    REP (i,n) {
        mn = min(mn,sa.lcp[i]);
        if (!ban[sa.sa[i]]) {
            ans = max(ans,n-sa[i]);
            hei.eb(mn);
            mn = INF;
        }
    }

    vector<ll> l(SZ(hei));
    vector<ll> r(SZ(hei));


    vector<ll> stk;
    REP (i,SZ(hei)) {
        while (!stk.empty() && hei[stk.back()] >= hei[i]) {
            stk.pop_back();
        }
        l[i] = SZ(stk) ? stk.back() + 1 : 0;
        stk.eb(i);
    }

    stk.clear();
    RREP (i,SZ(hei)-1) {
        while (!stk.empty() && hei[stk.back()] >= hei[i]) {
            stk.pop_back();
        }
        r[i] = SZ(stk) ? stk.back() - 1 : SZ(hei)-1;
        stk.eb(i);
    }

    debug(hei);
    debug(l);
    debug(r);

    REP (i,SZ(hei)) {
        ans = max(ans,hei[i]*(r[i]-l[i]+2));
    }

    cout << ans << endl;
    return 0;
}
