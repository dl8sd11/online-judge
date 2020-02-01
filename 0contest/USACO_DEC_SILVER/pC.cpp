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
const ll MAXN=105;
const ll MAXLG=__lg(MAXN)+2;


ll n,k;
ll b[MAXN][12];
bool vis[MAXN][12];

ll dx[] = {1,0,-1,0};
ll dy[] = {0,1,0,-1};

inline bool valid(ll x,ll y) {
    return x >= 0 && x < n && y >= 0 && y < 10;
}

vector<pii> q;
void DFS(ll x,ll y) {
    vis[x][y] = true;
    q.emplace_back(x,y);
    REP (i,4) {
        ll cx = x + dx[i];
        ll cy = y + dy[i];
        if (valid(cx,cy) && b[cx][cy] == b[x][y] && !vis[cx][cy]) {
            DFS(cx,cy);
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    freopen("mooyomooyo.in","r",stdin);
    freopen ("mooyomooyo.out","w",stdout);
    cin >> n >> k;
    REP (i,n) {
        REP (j,10) {
            char c;
            cin >> c;
            b[i][j] = c-'0';
        }
    }

    while (true) {
        MEM(vis,0);
        debug("tmd");

        ll tb[MAXN][MAXN];
        REP (i,n) {
            REP (j,10) {
                tb[i][j] = b[i][j];
            }
        }

        REP (i,n) {
            REP (j,10) {
                if (!vis[i][j] && b[i][j] != 0) {
                    DFS(i,j);
                    if (q.size() >= k) {
                        for (auto p:q) {
                            b[p.X][p.Y] = 0;
                        }
                    } 
                    q.clear();
                }
            }
        }

        bool flag = true;
        REP (i,n) {
            REP (j,10) {
                if (b[i][j] != tb[i][j]) {
                    flag = false;
                }
            }
        }

        if (flag) {
            break;
        }

        REP (j,10) {
            vector<ll> tmp;
            REP (i,n) {
                if (b[i][j] != 0) {
                    tmp.eb(b[i][j]);
                }
            }

            for (ll i=n-1;i>=0;i--)  {
                if (tmp.size()) {
                    b[i][j] = tmp.back();
                    tmp.pop_back();
                } else {
                    b[i][j] = 0;
                }
            }
        }
    }
    REP (i,n) {
        REP (j,10) {
            cout << b[i][j];
        }
        cout << endl;
    }
    return 0;
}
