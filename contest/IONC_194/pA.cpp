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
// const ll MAXN = 

int h, m, dh, dm;
string dt, line;
/********** Good Luck :) **********/
int main()
{
    IOS();

    while (getline(cin, line)) {
        stringstream ss;
        ss << line;
        vector<string> ans;
        while (ss >> h >> m >> dt) {

            if (SZ(dt) == 5) {
                dh = dt[4] - '0';
                dm = 0;
            } else {
                dh = dt[4] - '0';
                dm = dt[6] - '0';
            }
            m = h*60 + m;

            if (dt[3] == '+') {
                m -= (dh - 8) * 60;
                m -= dm * 6;
            } else {
                m += (dh + 8) * 60;
                m += dm * 6;
            }
            debug(dh, dm, m);
            m %= 60 * 24;
            while (m < 0) {
                m += 60*24;
            }


            h = m/ 60;
            m %= 60;

            assert(m >= 0 && m < 60);
            assert(h >= 0 && h < 24);

            string tmp;
            if (h < 10) {
                tmp += "0";
            }
            tmp += to_string(h);
            tmp += ":";
            if (m < 10) {
                tmp += "0";
            }
            tmp += to_string(m);
            ans.eb(tmp);
        }

        REP (i, SZ(ans)) {
            if (i != 0) {
                cout << " ";
            }
            cout << ans[i];
        }
        cout << endl;
    }
    return 0;
}
