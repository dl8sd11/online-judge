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
const ll MAXN = 1003;

ll t,n,ans;
vector<string> str;
bool vis[MAXN];

void solve(vector<ll> id,ll sm) {
    debug(id,sm);
    if (id.size() == 1) {
        return;
    }
    vector<ll> cid[26];
    for (auto i : id) {
        if (sm + 1 < SZ(str[i])) {
            cid[str[i][sm+1]-'A'].eb(i);
        }
    }

    REP (i,26) {
        if (SZ(cid[i]) > 0) {
            solve(cid[i],sm+1);
        }
    }
    vector<ll> nvis;
    for (auto i : id) {
        if (!vis[i]) {
            nvis.eb(i);
        }
    }

    if (sm != -1 && nvis.size() >= 2) {
        vis[nvis.front()] = true;
        vis[nvis.back()] = true;
        ans += 2;
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    REP1 (test,t) {
        cin >> n;
        str.clear();
        ans = 0;
        REP (i,n) {
            string s;
            cin >> s;
            reverse(ALL(s));
            str.eb(s);
        }
        vector<ll> id;
        REP (i,n) {
            id.eb(i);
        }

        MEM(vis,0);
        solve(id,-1);

        cout << "Case #" << test << ": " << ans << endl;
    }
    return 0;
}
