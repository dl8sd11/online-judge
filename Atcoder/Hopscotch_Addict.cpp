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
#define ever (;;)
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
const ll MAXN = 100005;

int n, m, s, t, dis[3][MAXN];
bool vis[3][MAXN];
vector<int> edge[MAXN];

struct State {
    int nd, md, dd;
    bool operator < (const State & st) const{
        return dd > st.dd;
    }
};
priority_queue<State> pq;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
    }
    cin >> s >> t;

    MEM(dis, iNF);
    dis[0][s] = 0;
    pq.push({s, 0, 0});

    for ever {
        State fnd = {-1, -1, -1};
        while (!pq.empty()) {
            fnd = pq.top();
            if (vis[fnd.md][fnd.nd]) {
                pq.pop();
            } else {
                break;
            }
        }
        if (fnd.nd == -1) {
            break;
        }
        debug(fnd.nd, fnd.md, fnd.dd);
        vis[fnd.md][fnd.nd] = true;

        for (auto v : edge[fnd.nd]) {
            debug(fnd.nd, v);
            if (dis[(fnd.md+1)%3][v] > dis[fnd.md][fnd.nd] + 1) {
                dis[(fnd.md+1)%3][v] = dis[fnd.md][fnd.nd] + 1;
                pq.push({v, (fnd.md+1)%3, dis[(fnd.md+1)%3][v]});
            }
        }
    }
    
    if (dis[0][t] == iNF) {
        cout << -1 << endl;
    } else {
        cout << dis[0][t]/3 << endl;
    }
    return 0;
}
