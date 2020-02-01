#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
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
const ll MAXN = 10004;

ll n, m, a[MAXN];
vector<pii> edge[MAXN];
ll scnt;
vector<ll> st;
ll dis[MAXN];
bool vis[MAXN];
priority_queue<pii, vector<pii>, greater<pii> > pq;
ll id[MAXN];
vector<pii> szvec;
ll wm[MAXN];


namespace SEGSR {
    int n;
    ll dt[MAXN*2];

    // params
    const ll les = -INF;
    inline ll opr(ll v1,ll v2) {
        return max(v1,v2);
    }
    inline void up(ll &x,ll val) {
        x = val;
    }

    void init(int in) {
        n = in;
        for (int i=n-1;i>0;i--) {
            dt[i] = opr(dt[i<<1],dt[i<<1|1]);
        }
    }

    void upd(int pos,ll val) {
        for (up(dt[pos+=n],val);pos>1;pos>>=1) {
            dt[pos>>1] = opr(dt[pos],dt[pos^1]);
        }
    }

    ll qry(int l,int r) {
        ll ret = les;
        for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
            if (l&1) {
                ret = opr(ret,dt[l++]);
            }
            if (r&1) {
                ret = opr(ret,dt[--r]);
            }
        }
        return ret;
    }
}

ll rev[MAXN];
void chg(ll p, ll v) {
    SEGSR::upd(rev[p], v);
}

ll qry(ll k) {
    int l = 0, r = n;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        if (szvec[mid].X <= k) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return SEGSR::qry(0, l + 1);
}

void build() {
    debug("HI");
    MEM(dis, INF);
    for (auto v : st) {
        dis[v] = 0;
        pq.emplace(0, v);
    }

    while (true) {
        ll fnd = -1;
        while (pq.size() && vis[fnd=pq.top().Y]) {
            pq.pop();
        }
        if (fnd == -1) {
            break;
        }
        vis[fnd] = 1;

        for (auto p : edge[fnd]) {
            if (dis[p.X] > dis[fnd] + p.Y) {
                dis[p.X] = dis[fnd] + p.Y;
                pq.emplace(dis[p.X], p.X);
            }
        }
    }

    pary(dis+1, dis+n+1);
    debug("HI");

    REP1 (i, n) {
        szvec.eb(dis[i], i);
    }
    sort(ALL(szvec));

    REP (i, n) {
        id[i] = szvec[i].Y;
        rev[szvec[i].Y] = i;
        wm[i] = a[szvec[i].Y];
        SEGSR::dt[i+n] = a[szvec[i].Y];
    }
    SEGSR::init(n);

    pary(id+1, id+n+1);
    debug(szvec);
    pary(wm,wm+n);

}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP1 (i, n) {
        cin >> a[i];
    }

    REP (i, m) {
        ll u, v, c;
        cin >> u >> v >> c;
        edge[u].eb(v, c);
        edge[v].eb(u, c);
    }

    cin >> scnt;
    REP (i, scnt) {
        ll d;
        cin >> d;
        st.eb(d);
    }

    build();

    int q, p, v, cmd;
    cin >> q;
    while (q--) {
        cin >> cmd;
        if (cmd == 1) {
            cin >> p >> v;
            chg(p, v);
        } else {
            cin >> p;
            cout << qry(p) << endl;
        }
    }
    return 0;
}
