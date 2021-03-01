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
// #define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll MAXN = 

ll n,cnt;
vector<pii> ans;
ll Q(pii f,pii s) {
    cout << "? " << f.X << " " << f.Y << " " << s.X << " " << s.Y << endl;
    cin >> cnt;
    return cnt;
}

void solve(pii f,pii s) {
    if (f == s) {
        ans.eb(f);
    } else {
        if (f.X != s.X) {
            ll mid = (f.X + s.X) / 2;
            if (Q(f,pii(mid,s.Y)) & 1) {
                solve(f,pii(mid,s.Y));
            } else {
                solve(pii(mid+1,f.Y),s);
            }
        } else {
            ll mid = (f.Y + s.Y) / 2;
            if (Q(f,pii(s.X,mid)) & 1) {
                solve(f,pii(s.X,mid));
            } else {
                solve(pii(f.X,mid+1),s);
            }

        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    srand(time(0));

    cin >> n;
    vector<pii> query;
    REP1 (i,n - 1) {
        query.eb(n,i);
        query.eb(i,n);
    }
    random_shuffle(ALL(query));

    pii fnd = {INF,INF};
    for (auto q : query) {
        if (Q(pii(1,1),q) & 1) {
            fnd = q;
            break;
        }
    }

    assert(fnd.X != INF);

    if (fnd.X == n) {
        solve(pii(1,1),fnd);
        solve(pii(1,fnd.Y+1),pii(n,n));
    } else {
        solve(pii(1,1),fnd);
        solve(pii(fnd.X+1,1),pii(n,n));
    }

    cout << "! " << ans[0].X << " " << ans[0].Y << " " << ans[1].X << " " << ans[1].Y << endl;
    return 0;
}
