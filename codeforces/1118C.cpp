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

ll n,cnt[MAXN],a[30][30];
vector<ll> one,two,four;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n*n) {
        ll num;
        cin >> num;
        cnt[num]++;
    }

    REP (i,MAXN) {
        REP (j,cnt[i]/4) {
            four.emplace_back(i);
        }
        cnt[i] = cnt[i] % 4;
        if (cnt[i] / 2) {
            two.emplace_back(i);
        }
        if (cnt[i] & 1) {
            one.emplace_back(i);
        }
    }

    bool flag = true;
    REP (i,n/2) {
        REP (j,n/2) {
            if (four.size()) {
                a[i][j] = a[n-i-1][j] = a[i][n-j-1] = a[n-i-1][n-j-1] = four.back();
                four.pop_back();
            } else {
                flag = false;
            }
        }
    }

    if (n & 1) {
        for (auto idx : four) {
            two.emplace_back(idx);
            two.emplace_back(idx);
        }
        REP (i,n/2) {
            if (two.size()) {
                a[i][n/2] = a[n-i-1][n/2] = two.back();
                two.pop_back();
            } else {
                flag = false;
            }
        }
        REP (i,n/2) {
            if (two.size()) {
                a[n/2][i] = a[n/2][n-i-1] = two.back();
                two.pop_back();
            } else {
                flag = false;
            }
        }
        if (one.size()) {
            a[n/2][n/2] = one.back();
        } else {
            flag = false;
        }
    }

    if (flag) {
        cout << "YES" << endl;
        REP (i,n) {
            REP (j,n) {
                cout << a[i][j] << " \n"[j==n-1];
            }
        }
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
