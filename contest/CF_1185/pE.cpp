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
const ll MAXN = 2003;

ll t,n,m;
char g[MAXN][MAXN];
vector<pair<pii,pii> > ans;

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
        cin >> n >> m;
        ans.clear();
        ll scnt = 0;
        REP (i,n) {
            REP (j,m) {
                cin >> g[i][j];
                if (g[i][j] >= 'a' && g[i][j] <= 'z') {
                    scnt = max(scnt,g[i][j]-'a'+1LL);
                } 
            }
        }


        bool sol = true;
        RREP (cur,scnt-1) {
            pii st = {INF,INF}, ed = {-INF,-INF};
            REP (i,n) {
                REP (j,m) {
                    if (g[i][j] == 'a' + cur) {
                        st = min(st,pii(i,j));
                        ed = max(ed,pii(i,j));
                    }
                }
            }

            debug(st,ed);
            bool flag = true;
            if (st.X == INF) {
                ans.eb(ans.back());
            } else if (st.X == ed.X || st.Y == ed.Y) {
                for (ll x=st.X; x<=ed.X;x++) {
                    for (ll y=st.Y;y<=ed.Y;y++) {
                        if (g[x][y] != 'a'+cur && g[x][y] != '*') {
                            flag = false;
                        }
                    }
                }
                if (flag) {
                    for (ll x=st.X; x<=ed.X;x++) {
                        for (ll y=st.Y;y<=ed.Y;y++) {
                            g[x][y] = '*';
                        }
                    }
                    ans.eb(st,ed);
                } else {
                    sol = false;
                    break;
                }
            } else {
                sol = false;
                break;
            }

        }

        REP (i,n) {
            REP (j,m) {
                if (g[i][j] >= 'a' && g[i][j] <= 'z') {
                    sol = false;
                }
            }
        }

        // debug(ans);
        if (sol) {
            cout << "YES" << endl;
            cout << SZ(ans) << endl;
            RREP (i,SZ(ans)-1) {
                cout << ans[i].X.X+1 << " " <<  ans[i].X.Y+1 << " " <<  ans[i].Y.X+1 << " " << ans[i].Y.Y+1 << endl;
            }
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
