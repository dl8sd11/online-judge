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
// const ll MAXN = 


string str;
ll n;
map<char,char> mir;
bool m[300];
/********** Good Luck :) **********/
int main()
{
    IOS();
    getline(cin,str);
    n = SZ(str);

    m['o'] = true;
    m['v'] = true;
    m['w'] = true;
    m['x'] = true;
    m['8'] = true;

    mir['o'] = 'o';
    mir['v'] = 'v';
    mir['w'] = 'w';
    mir['x'] = 'x';
    mir['8'] = '8';
    mir['b'] = 'd';
    mir['d'] = 'b';
    mir['p'] = 'q';
    mir['q'] = 'p';


    string ans;
    for (ll i=0;i<n;i++) {
        if (m[str[i]]) {
            for (ll j=0;j+i<n&&i-j>=0;j++) {
                if (mir[str[i+j]] != str[i-j]) {
                    break;
                }
                if (j*2+1 > SZ(ans)) {
                    ans = str.substr(i-j,j*2+1);
                }
            }
        }
    }

    for (ll i=0;i<n-1;i++) {
        for (ll j=1;i-j+1>=0&&i+j<n;j++) {
            if (mir[str[i-j+1]] != str[i+j]) {
                break;
            }
            if (j*2 > SZ(ans)) {
                ans = str.substr(i-j+1,j*2);
            }
        }
    }

    if (SZ(ans) == 0) {
        cout << "..." << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
