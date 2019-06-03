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
const ll MAXN = 100005;

string str;
struct SuffixArray {
    string s;
    ll n;
    vector<ll> sa,rk,hei,t;
    SuffixArray(string si): s(si),n(SZ(s)),sa(n),rk(n),hei(n),t(n) {
        REP (i,n) {
            rk[sa[i]=i] = s[i];
        }
        t[n-1] = -1;
        for (ll h=1;t[n-1] != n-1; h <<= 1) {
            auto cmp = [&](ll i,ll j) {
                if (rk[i] != rk[j]) {
                    return rk[i] < rk[j];
                } else {
                    return (i+h < n && j+h < n) ? (rk[i+h] < rk[j+h]) : (i > j);
                } 
            };
            sort(ALL(sa),cmp);
            t[0] = 0;
            REP1 (i,n-1) {
                t[i] = t[i-1] + cmp(sa[i-1],sa[i]);
            }
            REP (i,n) {
                rk[sa[i]] = t[i];
            }
        }
        ll con = 0;
        REP (i,n) {
            if (rk[i] == 0) {
                hei[0] = con = 0;
            } else {
                if (con) {
                    con--;
                }
                while (s[i+con] == s[sa[rk[i]-1]+con]) {
                    con++;
                }
                hei[rk[i]] = con;
            }
        }
    }
    ll operator [] (ll idx) {
        return sa[idx];
    }
};

namespace SEG {
    ll n,seg[MAXN*2];
    void build() {
        for (ll i=n-1;i>0;i--) {
            seg[i] = min(seg[i<<1],seg[i<<1|1]);
        }
    }
    ll query(ll l,ll r) {
        ll ret = INF;
        for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
            if (l&1) {
                ret = min(ret,seg[l++]);
            }
            if (r&1) {
                ret = min(ret,seg[--r]);
            }
        }
        return ret;
    }
}
vector<pii> ans;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> str;
    SuffixArray sa(str);
    SEG::n = SZ(str);
    REP (i,SEG::n) {
        SEG::seg[i+SEG::n] = sa.hei[i];
    }
    SEG::build();

    ll hp = sa.rk[0];
    REP (i,SZ(str)) {
        pii q = {hp,sa.rk[i]};
        if (q.X > q.Y) {
            swap(q.X,q.Y);
        }
        debug(q,SEG::query(q.X,q.Y+1));
        if (SEG::query(q.X+1,q.Y+1) >= SZ(str)-i) {
            ll ret = 1;
            ll L = -1,R = sa.rk[i];
            while (L < R - 1) {
                ll mid = (L + R) >> 1;
                if (SEG::query(mid+1,sa.rk[i]+1) >= SZ(str) - i) {
                    R = mid;
                } else {
                    L = mid;
                }
            }
            ret += sa.rk[i] - R;
            L = sa.rk[i], R = sa.n;
            while (L < R - 1) {
                ll mid = (L + R) >> 1;
                if (SEG::query(sa.rk[i]+1,mid+1) >= SZ(str) - i) {
                    L = mid;
                } else {
                    R = mid;
                }
            }
            ret += L - sa.rk[i];
            ans.eb(SZ(str)-i,ret);
        }
    }

    cout << SZ(ans) << endl;
    for (ll i=SZ(ans)-1;i>=0;i--) {
        cout << ans[i].X << " " << ans[i].Y << endl;
    }
    return 0;
}
