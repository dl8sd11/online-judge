#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
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
const int iNF = 0x3f3f3f3f;
const ll MAXN = 1000006;

ll t, n, a[MAXN], f;

namespace Loop{
    vector<int> hit[MAXN];

    void build() {
        hit[1] = {};
        hit[2] = {};
        hit[3] = {3};
        for (int i=4;i < MAXN;i++) {
            hit[i] = hit[(i+1)>>1];
            for (auto &h : hit[i]) {
                h = (h<<1)-1;
            }
            if (i&1) {
                hit[i].eb(i);
            }
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    Loop::build();
    cin >> t;
    while (t--) {
        cin >> n;
        REP (i, n-1) {
            cin >> a[i];
        }
        cin >> f;

        deque<ll> id;
        REP (i, n-1) {
            id.eb(i);
        }

        pii ans = {INF, INF};
        REP (i, n-1) {
            ll dmg = (i & 1 ? a[i-1] : 0);
            for (auto h : Loop::hit[SZ(id)]) {
                dmg += a[id[h - 1]];
            }
            ll hp = a[i];

            if (hp <= f) {
                pii cur = {dmg + f, i};
                ans = min(cur, ans);
            }

            if (i & 1 ^ 1) {
                id.eb(id.front());
            } 
            id.pop_front();
        }

        if (ans.Y < INF) {
            cout << "possible" << endl;
            cout << ans.Y+1 << " " << ans.X << endl;
        } else {
            cout << "impossible" << endl;
        }
    }
    return 0;
}
