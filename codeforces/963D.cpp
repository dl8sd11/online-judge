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
const ll MAXN = 100001;

struct SuffixArray  {
    ll n;
    vector<ll> sa,rk;
    SuffixArray (const string &str) : n(SZ(str)), sa(n), rk(n) {
        vector<ll> t(n);
        REP (i,n) {
            rk[sa[i]=i] = str[i];
        }
        for (ll h=1;t[n-1] != n-1;h *= 2) {
            auto cmp = [&](ll i,ll j) {
                if (rk[i] != rk[j]) {
                    return rk[i] < rk[j];
                } else {
                    return i+h < n && j+h < n ? rk[i+h] < rk[j+h] : i > j;
                }
            };
            sort(ALL(sa),cmp);
            REP (i,n-1) {
                t[i+1] = t[i] + cmp(sa[i],sa[i+1]);
            }
            REP (i,n) {
                rk[sa[i]] = t[i];
            }
        }
    }

    ll mn[MAXN*2],mx[MAXN*2];
    void build() {
        for (ll i=n*2-1;i>=1;i--) {
            if (i >= n) {
                mn[i] = sa[i-1];
                mx[i] = sa[i-1];
            } else {
                mn[i] = min(mn[i<<1],mn[i<<1|1]);
                mx[i] = max(mx[i<<1],mx[i<<1|1]);
            }
        }
    }

    ll query(ll l,ll r) {
        ll rmx=-1,rmn = 2*n;
        for (l+=n,r+=n;l < r;l>>=1,r>>=1) {
            if (l&1) {
                rmx = max(rmx,mx[l]);
                rmn = min(rmn,mx[l]);
                l++;
            }
            if (r&1) {
                r--;
                rmx = max(rmx,mx[r]);
                rmn = min(rmn,mn[r]);
            }
        }
        return rmx - rmn;
    }
    ll operator [] (ll idx) {
        return sa[idx];
    }
};


string str;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> str;
    SuffixArray sa(str);
    debug(sa.sa);

    ll q;
    cin >> q;
    while (q--) {
        ll k;
        string m;
        cin >> k >> m;

        function<ll (string)> lbd = [&](string s) {
            ll L = -1, R = sa.n;
            while (L < R - 1) {
                ll mid = (L + R) >> 1;
                bool gq = true;
                REP (i,SZ(s)) {
                    if (sa[mid]+i >= sa.n) {
                        gq = false;
                        break;
                    } else if (str[sa[mid]+i] < m[i]){
                        gq = false;
                        break;
                    } else if (str[sa[mid]+i] > m[i]) {
                        break;
                    }
                }
                if (gq) {
                    R = mid;
                } else {
                    L = mid;
                }
            }
            return R;
        };

        ll L = lbd(m);
        m.back()++;
        ll R = lbd(m);
        debug(m,L,R);

        if (R-L >= k) {
            cout << "This problem is too hard QQ" << endl;
        } else {
            cout << -1 << endl;
        }
        // debug(L,R);
    }
    return 0;   
}
