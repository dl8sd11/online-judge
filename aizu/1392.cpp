#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<int, ll> pli;
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
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 4003;

string a, b;
int n, m;
int nxta[MAXN][2];
int nxtb[MAXN][2];

int id (int x,int y) {
    return x * (m+2) + y;
}

pii rid (int v) {
    return pii(v/(m+2), v%(m+2));
}

int tran[MAXN*MAXN];
int prv[MAXN*MAXN];
int dis[MAXN*MAXN];
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> a >> b;
    n = SZ(a), m = SZ(b);
    vector<int> lst = {n+1, n+1};
    nxta[n+1][0] = n+1;
    nxta[n+1][1] = n+1;
    nxtb[m+1][0] = m+1;
    nxtb[m+1][1] = m+1;
    RREP (i, n) {
        nxta[i][0] = lst[0];
        nxta[i][1] = lst[1];
        if (i) {
            lst[a[i-1]-'0'] = i;
        }
    }

    lst = {m+1, m+1};
    RREP (i, m) {
        nxtb[i][0] = lst[0];
        nxtb[i][1] = lst[1];
        if (i) {
            lst[b[i-1]-'0'] = i;
        }
    }

    queue<int> bfs;
    bfs.emplace(0);
    MEM(dis, iNF);
    dis[0] = 0;

    debug(nxta[0][0], nxtb[0][0]);
    debug(nxta[0][1], nxtb[0][1]);
    while (!bfs.empty()) {
        int cur = bfs.front(), x, y;
        bfs.pop();
        tie(x, y) = rid(cur);
        debug(x, y);

        int nx0 = id(nxta[x][0], nxtb[y][0]);
        int nx1 = id(nxta[x][1], nxtb[y][1]);
        debug(rid(nx0));
        debug(rid(nx1));

        if (dis[nx0] == iNF) {
            bfs.emplace(nx0);
            dis[nx0] = dis[cur] + 1;
            tran[nx0] = 0;
            prv[nx0] = cur;
        }
        if (dis[nx1] == iNF) {
            bfs.emplace(nx1);
            dis[nx1] = dis[cur] + 1;
            tran[nx1] = 1;
            prv[nx1] = cur;
        }
    }

    vector<bool> ans;
    int x = n+1, y = m+1;
    while (x && y) {
        ans.eb(tran[id(x, y)]);
        tie(x, y) = rid(prv[id(x, y)]);
    }

    RREP (i, SZ(ans)-1) {
        cout << ans[i];
    }
    cout << endl;
    return 0;
}
