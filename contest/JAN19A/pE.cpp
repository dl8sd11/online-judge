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
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;

ll t,n;
bool color[MAXN];
vector<ll> edge[MAXN];
ll cnt1,cnt2;
void DFS(ll nd,ll par) {
    color[nd] = !color[par];
    if (color[nd]) {
        cnt1++;
    } else {
        cnt2++;
    }
    for (auto v:edge[nd]) if (v != par) {
        DFS(v,nd);
    }
}
ll cnt;
void DFS2(ll nd,ll par) {
    color[nd] = (cnt++)&1;
    for (auto v:edge[nd]) if (v != par) {
        DFS2(v,nd);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
        cin >> n;
        REP1 (i,n) {
            edge[i].clear();
        }
        
        REP (i,n-1) {
            ll u,v;
            cin >> u >> v;
            edge[u].eb(v);
            edge[v].eb(u);
        }


        cnt1 = 0,cnt2 = 0;
        DFS(1,1);
        if (cnt1 == cnt2) {
            cout << 1 << endl;
        } else {
            cout << 2 << endl;
            cnt = 0;
            DFS2(1,1);
        }
        vector<ll> g1,g2;
        REP1 (i,n) {
            if (color[i]) {
                g1.eb(i);
            } else {
                g2.eb(i);
            }
        }

        REP (i,n/2) {
            cout << g1[i] << " \n"[i==n/2-1];
        } 
        REP (i,n/2) {
            cout << g2[i] << " \n"[i==n/2-1];
        } 
    }
    return 0;
}
