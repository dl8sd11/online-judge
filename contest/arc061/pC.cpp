#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
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
#define TIME(i) Timer i(#i)
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
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 100005;

int n, m;
vector<pii> edge[MAXN];
map<int, int> dis[MAXN];
set<int> vis[MAXN];
bool slv[MAXN];

typedef pair<int, pii> piii;
priority_queue<piii, vector<piii>, greater<piii> > pq;
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int u, v, c;
        cin >> u >> v >> c;
        edge[u].eb(c, v);
        edge[v].eb(c, u);
    }

    REP1 (i, n) {
        sort(ALL(edge[i]));
    }
    debug(edge[6]);
    debug(edge[7]);

    MEM(slv, 0);
    dis[1][0] = 0;
    pq.emplace(0, pii(1, 0));

    while (true) {
        pii fnd = {-1, -1};
        while (!pq.empty()) {
            fnd = pq.top().Y;
            pq.pop();
            if (vis[fnd.X].count(fnd.Y) == 0) {
                break;
            }
        }
        if (fnd.X == -1) {
            break;
        } else if (vis[fnd.X].count(fnd.Y) == 1) {
            break;
        }
        vis[fnd.X].insert(fnd.Y);

        int bs = dis[fnd.X][fnd.Y];
        debug(fnd, bs);
        if (!slv[fnd.X]) {
            for (auto e : edge[fnd.X]) {
                if (e.X == fnd.Y) {
                    if (dis[e.Y].count(e.X) == 0 || dis[e.Y][e.X] > bs) {
                        dis[e.Y][e.X] = bs;
                        pq.emplace(bs, pii(e.Y, e.X));
                    }
                } else {
                    if (dis[e.Y].count(e.X) == 0 || dis[e.Y][e.X] > bs + 1) {
                        dis[e.Y][e.X] = bs + 1;
                        pq.emplace(bs + 1, pii(e.Y, e.X));
                    }
                }
            }
            slv[fnd.X] = true;
        } else {
            auto ed = upper_bound(ALL(edge[fnd.X]), pii(fnd.Y, iNF));
            for (auto e = lower_bound(ALL(edge[fnd.X]), pii(fnd.Y, -1)); e != ed; e++) {
                if (dis[e->Y].count(e->X) == 0 || dis[e->Y][e->X] > bs) {
                    dis[e->Y][e->X] = bs;
                    pq.emplace(bs, pii(e->Y, e->X));
                }
            }
        }
    }
    
    if (dis[n].empty()) {
        cout << -1 << endl;
    } else {
        int ans = iNF;
        for (auto d : dis[n]) {
            ans = min(ans, d.Y);
        }
        cout << ans << endl;
    }

    return 0;
}
