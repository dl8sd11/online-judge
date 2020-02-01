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
const ll MAXN = 1003;

ll n;

namespace SMALL {
    bitset<MAXN> bs[MAXN];
    bool a[MAXN][MAXN];

    void solve() {

        vector<ll> permu;
        REP (i,n) {
            permu.eb(i);
        }

        REP (i,n) {
            REP (j,n) {
                a[i][j] = 0;
            }
        }
        REP (i,n) {
            REP (j,n) {
                bs[i][j] = false;
            }
        }

        REP (i,n) {
            vector<ll> ch;
            bool suc = false;
            REP (tr,2000) {
                ch.clear();
                random_shuffle(ALL(permu));
                bitset<MAXN> cur;
                ll sum = 0;
                for (auto p : permu) {
                    if (!cur[p]) {
                        sum++;
                        ch.eb(p);
                        if (sum == 8) {
                            break;
                        }
                        cur |= bs[p];
                    }
                }
                if (sum == 8) {
                    suc = true;
                    break;
                }
            }
            if (!suc) {
                debug("fail");
                REP (x,n) {
                    REP (j,n) {
                        a[x][j] = 0;
                    }
                }
                REP (i,n) {
                    REP (j,n) {
                        bs[i][j] = false;
                    }
                }
                i = -1;
                continue;
            }

            for (auto v : ch) {
                a[i][v] = true;
                for (auto e : ch) {
                    bs[v][e] = true;
                }
            }

        }
        
        ll tot = 0;
        REP (i,n) {
            REP (j,n) {
                cout << (a[i][j] ? 'O' : '.');
                tot += a[i][j];
            }
            cout << endl;
        }
        debug(tot);
        assert(tot >= 8*n);
    }
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    srand(910607);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n;
        SMALL::solve();
    }


    return 0;
}
