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
const int nINF = 0x8f8f8f8f;
const int iNF = 0x3f3f3f3f;
const int MAXN = 1003;

string c, s, t;
int lcps[51][26], lcpt[51][26], dp[MAXN][51][51];

void upd(int i, int ms, int mt, int cid) {
    int dt = (lcps[ms][cid] == SZ(s)) - (lcpt[mt][cid] == SZ(t));
    int &ns = dp[i+1][lcps[ms][cid]][lcpt[mt][cid]];
    ns = max(ns, dt + dp[i][ms][mt]);
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> c >> s >> t;
    // preprocessing
    REP (i, SZ(s)+1) {
        for (char ch='a';ch<='z';ch++) {
            string cur = s.substr(0,i) + ch;
            for (int mt=i+1;mt>=0;mt--) {
                if (cur.substr(i+1-mt) == s.substr(0,mt)) {
                    lcps[i][ch-'a'] = mt;
                    break;
                }
            }
        }
    }

    REP (i, SZ(t)+1) {
        for (char ch='a';ch<='z';ch++) {
            string cur = t.substr(0,i) + ch;
            for (int mt=i+1;mt>=0;mt--) {
                if (cur.substr(i+1-mt) == t.substr(0,mt)) {
                    lcpt[i][ch-'a'] = mt;
                    break;
                }
            }
        }
    }

    // solve
    MEM(dp, -INF);
    dp[0][0][0] = 0;
    int ans = -INF;
    REP (i, SZ(c)) {
        REP (ms, SZ(s)+1) {
            REP (mt, SZ(t)+1) {
                if (c[i] == '*') {
                    REP (ch, 26) {
                        upd(i, ms, mt, ch);
                    }
                } else {
                    upd(i, ms, mt, c[i]-'a');
                }
            }
        }
    }

    REP (ms, SZ(s)+1) {
        REP (mt, SZ(t)+1) {
            ans = max(dp[SZ(c)][ms][mt], ans);
        }
    }

    cout << ans << endl;
    return 0;
}
