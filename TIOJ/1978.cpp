#include <bits/stdc++.h>
using namespace std;
typedef int ll;
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
const ll MAXN = 81;

typedef bitset<MAXN> bs;

bs edge[MAXN], emp;
int n, m, p[MAXN], ans;

void max_clique (bs R, bs P, bs X) {
    debug(R, P, X);
    if(P==emp && X==emp) {
        ans=max(ans,(int)R.count());
        return;
    }
    if (double(clock())/CLOCKS_PER_SEC > 1.899) return;
    if((R|P|X).count()<=ans) {
        return;
    }

    bs uni=P|X;
    int u, v;
    REP (uu, n){
        u=p[uu];
        if(uni[u]==1) break;
    }

    bs now2=P&~edge[u];
    for(int vv=0;vv<n;++vv){
        v=p[vv];
        if(now2[v]==1){
            R[v]=1;
            max_clique(R,P&edge[v],X&edge[v]);
            R[v]=0,P[v]=0,X[v]=1;
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    srand(time(0));
    cin >> n >> m;
    REP (i,m) {
        ll u,v;
        cin >> u >> v;
        edge[u][v] = true;
        edge[v][u] = true;
    }
    REP (i, n) {
        edge[i][i] = true;
        REP (j, n) {
            edge[i][j] = !edge[i][j];
        }
    }

    bs R, P, X;
    P.flip();
    REP (i, n) {
        p[i] = i;
    }
    random_shuffle(p, p+n);
    max_clique(R, P, X);

    cout << ans << endl;

    return 0;
}
