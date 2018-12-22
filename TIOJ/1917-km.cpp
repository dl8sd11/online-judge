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
const ll MAXN=525;
const ll MAXLG=__lg(MAXN)+2;


bool ban[MAXN][MAXN];
ll T,n,L,U,k,adj[MAXN][MAXN];
ll x[MAXN],y[MAXN],lx[MAXN],ly[MAXN];
ll xp[MAXN],yp[MAXN];
bool vx[MAXN],vy[MAXN];

bool DFS (ll ndx) {
    vx[ndx] = true;
    REP (ndy,n) {
        if (!vy[ndy]) {
            if (lx[ndx] + ly[ndy] == adj[ndx][ndy]) {
                vy[ndy] = true;
                if (yp[ndy] == -1 || DFS(yp[ndy])) {
                    xp[ndx] = ndy;
                    yp[ndy] = ndx;
                    return true;
                }
            }
        }
    }
    return false;
}
ll km () {
    MEM(lx,INF);
    MEM(ly,0);
    REP (i,n) {
        REP (j,n) {
            if (adj[i][j] != INF) {
                lx[i] = min(lx[i],adj[i][j]);
            }
        }
    }

    MEM(yp,-1);
    MEM(xp,-1);
    REP (u,n) {
        debug(u);
        ll cnt = 0;
        while (true) {
            if (cnt++ < 10) {
                pary(lx,lx+n);
                pary(lx,lx+n);
            }
            MEM(vx,0);
            MEM(vy,0);

            if (DFS(u)) {
                break;
            }
            ll d = INF;
            REP (i,n) if (vx[i]) {
                REP (j,n) if (!vy[j]){
                    if (adj[i][j] != INF) {
                        d = min(d,adj[i][j]-lx[i]-ly[j]);
                    }
                }
            }

            if (d == INF) {
                return -INF;
            }

            REP (i,n) {
                if (vx[i]) {
                    lx[i] += d;
                }
            }

            REP (j,n) {
                if (vy[j]) {
                    ly[j] -= d;
                }
            }


        }
    }

    ll weight = 0;
    REP (i,n) {
        weight += adj[i][xp[i]];
    }
    return weight;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> T;
    while (T--) {
        MEM(adj,INF);
        cin >> n >> L >> U >> k;
        REP (i,k) {
            ll u,v;
            cin >> u >> v; // banned
            ban[u][v] = true;
        }

        REP (i,n) {
            cin >> x[i];
        }

        REP (i,n) {
            cin >> y[i];
        }

        REP (i,n) {
            REP (j,n) {
                if (!ban[i][j]) {
                    if (x[i] + y[j] < L) {
                        adj[i][j] = 0;
                    } else if (x[i] + y[j] < U) {
                        adj[i][j] = x[i]+y[j]-L;
                    } else {
                        adj[i][j] = U-L;
                    }
                } else {
                    adj[i][j] = INF;
                }
            }
        }

        REP (i,n) {
            REP (j,n) {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }

        ll ans = km();
        if (ans == -INF) {
            cout << "no" << endl;
        } else {
            cout << ans << endl;
        }

    }
    return 0;
}
/*
1
4 9
0 3 3
0 0 100
0 2 5
1 1 400
2 0 4
2 2 30
3 1 200
3 3 700
3 2 100000
*/