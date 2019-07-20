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

int n, q, ans[MAXN], sz[MAXN], par[MAXN];
pair<int,int> qab[MAXN];
struct Query {
    int l, r;
    vector<int> id;
};
queue<Query> bfs;

void init() {
    REP1 (i, n) {
        sz[i] = i;
        par[i] = i;
    }
}

int fnd(int x) {
    return x == par[x] ? x : par[x] = fnd(par[x]);
}

void uni(int x, int y) {
    if (sz[x=fnd(x)] < sz[y=fnd(y)]) {
        swap(x, y);
    }
    if (x == y) {
        return;
    }
    par[y] = x;
    sz[x] += sz[y];
}

vector<int> edge[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> q;
    Query root = {n+1, 0, vector<int>()};
    REP (i, q) {
        cin >> qab[i].X >> qab[i].Y;
        root.id.eb(i);
    }
    bfs.push(root);

    REP1 (i, n) {
        for (int j=2; j*j<=i;j++) {
            if (i % j == 0) {
                edge[j].eb(i);
                edge[i/j].eb(i);
            }
        }
        if (i > 0) {
            edge[1].eb(i);
        }
    }

    int lay = 0;
    while (bfs.size()) {
        debug(lay++);
        init();
        int cur_sz = SZ(bfs), len = n;
        REP (blk, cur_sz) {
            Query cur_qry = bfs.front();
            bfs.pop();
            debug(blk);
            if (cur_qry.l == cur_qry.r+1) {
                for (auto id : cur_qry.id) {
                    ans[id] = cur_qry.r;
                }
                continue;
            }
            
            int m = (cur_qry.l + cur_qry.r) >> 1;
            while (len >= m) {
                debug(len, edge[len]);
                for (auto v : edge[len]) {
                    uni(v, v - len);
                }
                len--;
            }

            vector<int> lid, rid;
            for (auto id : cur_qry.id) {
                if (fnd(qab[id].X) == fnd(qab[id].Y)) {
                    lid.eb(id);
                } else {
                    rid.eb(id);
                }
            }

            debug(cur_qry.l, m, cur_qry.r);
            debug(cur_qry.id, lid, rid);
            if (SZ(lid)) {
                bfs.push({cur_qry.l, m, lid});
            }
            if (SZ(rid)) {
                bfs.push({m, cur_qry.r, rid});
            }
        }
    }

    REP (i, q) {
        cout << ans[i] << endl;
    }

    return 0;
}
