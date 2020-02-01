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
const ll MAXN = 1000003;

ll n;
ll cmd[MAXN];
pii child[MAXN];
bool st[MAXN],chg[MAXN];

void dfs(ll nd) {
    if (cmd[nd] >= 0) {
        st[nd] = cmd[nd];
        return;
    }else if (cmd[nd] == -1) {
        dfs(child[nd].X);
        dfs(child[nd].Y);
        st[nd] = st[child[nd].X] && st[child[nd].Y];
    } else if (cmd[nd] == -2) {
        dfs(child[nd].X);
        dfs(child[nd].Y);
        st[nd] = st[child[nd].X] ^ st[child[nd].Y];
    } else if (cmd[nd] == -3){
        dfs(child[nd].X);
        st[nd] = !st[child[nd].X];
    } else {
        dfs(child[nd].X);
        dfs(child[nd].Y);
        st[nd] = st[child[nd].X] || st[child[nd].Y];
    }
}

void solve(ll nd) {
    if (nd == 1) {
        chg[nd] = !st[nd];
    }
    ll L = child[nd].X,R = child[nd].Y;
    if (cmd[nd] == -1) {
        if (st[nd] == ((!st[L]) && st[R])) {
            chg[L] = st[1];
        } else {
            chg[L] = chg[nd];
        }
        if (st[nd] == ((st[L]) && (!st[R]))) {
            chg[R] = st[1];
        } else {
            chg[R] = chg[nd];
        }
        solve(L);
        solve(R);
    } else if (cmd[nd] == -2) {
        if (st[nd] == ((!st[L]) ^ st[R])) {
            chg[L] = st[1];
        } else {
            chg[L] = chg[nd];
        }
        if (st[nd] == ((st[L]) ^ (!st[R]))) {
            chg[R] = st[1];
        } else {
            chg[R] = chg[nd];
        }
        solve(L);
        solve(R);
    } else if (cmd[nd] == -3) {
        chg[L] = chg[nd];
        solve(L);
    } else if (cmd[nd] == -4) {

        if (st[nd] == ((!st[L]) || st[R])) {
            chg[L] = st[1];
        } else {
            chg[L] = chg[nd];
        }
        if (st[nd] == ((st[L]) || (!st[R]))) {
            chg[R] = st[1];
        } else {
            chg[R] = chg[nd];
        }
        solve(L);
        solve(R);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP1 (i,n) {
        string str;
        cin >> str;
        if (str[0] == 'I'){
            cin >> cmd[i];
        } else if (str[0] == 'A') {
            cmd[i] = -1;
            cin >> child[i].X >> child[i].Y;
        } else if (str[0] == 'X') {
            cmd[i] = -2;
            cin >> child[i].X >> child[i].Y;
        } else if (str[0] == 'N') {
            cmd[i] = -3;
            cin >> child[i].X;
        } else {
            cmd[i] = -4;
            cin >> child[i].X >> child[i].Y;

        }
    }

    
    dfs(1);
    pary(st+1,st+n+1);
    solve(1);
    pary(chg+1,chg+n+1);

    REP1 (i,n) {
        if (cmd[i] >= 0) {
            cout << chg[i];
        }
    }
    cout << endl;
    return 0;
}
