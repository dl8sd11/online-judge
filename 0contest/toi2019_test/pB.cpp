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
const ll MAXN = 3001;

struct Line {
    ll y,x,id;
    Line(ll yi,ll xi,ll d) {
        y = yi;
        x = xi;
        id = d;
        if (x < 0) {
            y *= -1;
            x *= -1;
        }
        ll g = __gcd(x,y);
        x /= g;
        y /= g;
        
    }
    bool operator == (const Line &l2) {
        return x == l2.x && y == l2.y;
    }
};

ll n;
pii p[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> p[i].X >> p[i].Y;
    }

    vector<ll> ans;
    REP (i,n) {
        vector<Line> lines;
        for (ll j=i+1;j<n;j++) {
            lines.eb(p[j].Y-p[i].Y,p[j].X-p[i].X,j);
        }
        sort(ALL(lines),[&](Line &l1,Line &l2){
            if (l1 == l2) {
                return l1.id < l2.id;
            } else {
                return l1.y*l2.x < l1.x*l2.y;

            }
        });
        for (auto l : lines) {
            debug(i,l.x,l.y,l.id);
        }
        
        REP (j,SZ(lines)) {
            if (j >= 2 && lines[j] == lines[j-1] && lines[j] == lines[j-2]) {
                vector<ll> tmp;
                tmp.eb(i);
                tmp.eb(lines[j].id);
                tmp.eb(lines[j-1].id);
                tmp.eb(lines[j-2].id);
                sort(ALL(tmp));
                if (ans.empty() || ans > tmp) {
                    ans = tmp;
                }
            }
        }
    }

    debug(ans);
    if (ans.empty()) {
        cout << 0 << endl;
    } else {
        assert(ans.size() == 4);
        REP (i,SZ(ans)) {
            cout << ans[i]+1 << " \n"[i==SZ(ans)-1];
        }

    }
    return 0;
}
