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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=2e3+5;
const ll MAXLG=__lg(MAXN)+2;


ll n,m;
vector<ll> edge[MAXN*2];
vector<ll> redge[MAXN*2];
ll st[MAXN*2],ptr;
bool vis[MAXN*2];

void DFS1(ll nd) {
    vis[nd] = true;
    for (ll i=0;i<SZ(edge[nd]);i++) {
        if (!vis[edge[nd][i]]) {
            DFS1(edge[nd][i]);
        }
    }
    st[ptr++] = nd;
}

ll comp[MAXN*2],cpc;
void DFS2(ll nd) {
    if (comp[nd]) return;
    comp[nd] = cpc;
    for (ll i=0;i<SZ(redge[nd]);i++) {
        DFS2(redge[nd][i]);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    while (cin>>n>>m) {
        REP (i,n*2) {
            edge[i].clear();
            redge[i].clear();
        }

        REP (i,m) {
            ll u,v,m1,m2;
            cin>>u>>v>>m1>>m2;
            edge[(u<<1)|m1].eb(((v<<1)|m2)^1);
            edge[(v<<1)|m2].eb(((u<<1)|m1)^1);
            redge[((v<<1)|m2)^1].eb((u<<1)|m1);
            redge[((u<<1)|m1)^1].eb((v<<1)|m2);
        }

        ptr = 0;
        MEM(vis,0);
        REP (i,n*2) {
            if (!vis[i]) {
                DFS1(i);
            }
        }

        cpc = 1;
        MEM(comp,0);
        for (ll i=ptr-1;i>=0;i--) {
            if (comp[st[i]] == 0) {
                DFS2(st[i]);
                cpc++;
            }
        }
        pary(comp,comp+2*n);

        bool ans = true;
        for (ll i=0;i<n;i++) {
            if (comp[i<<1] == comp[(i<<1)|1]) {
                ans = false;
            }
        }

        if (ans) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
