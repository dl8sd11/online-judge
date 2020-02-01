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


ll t,a,b;
vector<int> cur[10][100];
/********** Good Luck :) **********/
int main()
{
    IOS();

    REP (ba,10) {
        if (ba!=1 && (ba&1))continue;
        cur[ba][0].eb(ba);
        REP1 (i,100) {
            REP (j,SZ(cur[ba][i-1])) {
                int tmp = cur[ba][i-1][j] * 2;
                while (tmp) {
                    cur[ba][i].eb(tmp%10);
                    tmp/=10;
                }
            }
            if(SZ(cur[ba][i]) > 1500000) {
                debug(ba,i);
                break;
            }
        }
    }

    // ll sum = 0;
    // for (ll i=0;i<SZ(cur[1][58]);i++) {
    //     sum += SZ(cur[cur[1][58][i]][52]);
    // }
    // debug(sum);
    
    const ll ub = 58;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        if (a <= ub) {
            if (SZ(cur[1][a]) >= b) {
                cout << cur[1][a][SZ(cur[1][a])-b] << endl;
            } else {
                cout << -1 << endl;
            }
        } else if (a <= 113) {
            bool flag = true;
            for (ll i=SZ(cur[1][ub])-1;i>=0;i--) {
                if (SZ(cur[cur[1][ub][i]][a-ub]) >= b) {
                    cout << cur[cur[1][ub][i]][a-ub][SZ(cur[cur[1][ub][i]][a-ub])-b] << endl;
                    flag = false;
                    break;
                }
                b -= SZ(cur[cur[1][ub][i]][a-ub]);
            }
            if (flag) {
                cout << -1 << endl;
            }
        } else {
            a = 110 + (b%4);
            debug(b);
            bool flag = true;
            for (ll i=SZ(cur[1][ub])-1;i>=0;i--) {
                if (SZ(cur[cur[1][ub][i]][a-ub]) >= b) {
                    cout << cur[cur[1][ub][i]][a-ub][SZ(cur[cur[1][ub][i]][a-ub])-b] << endl;
                    flag = false;
                    break;
                }
                b -= SZ(cur[cur[1][ub][i]][a-ub]);
            }
            assert(!flag);
        }
    }
    return 0;
}
