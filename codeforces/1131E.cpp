#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
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
const int iNF = 0x3f3f3f3f;
// const ll MAXN = 

int n, bst[26], cur[26], lst[26];
char hd, tl;
string p;

pii build() {
    int pre = 1;
    int suf = 1;

    for (int i=1; i<SZ(p);i++) {
        if (p[i] == p[0]) {
            pre = i + 1;
        } else {
            break;
        }
    }

    for (int i=SZ(p)-2;i>=0;i--) {
        if (p[i] == p[SZ(p)-1]) {
            suf = SZ(p) - i;
        } else {
            break;
        }
    }

    MEM(cur, 0);
    int st = 0;
    for (int i=0; i<=SZ(p); i++) {
        if (i == SZ(p) || p[i] != p[st]) {
            cur[p[st]-'a'] = max(cur[p[st]-'a'], i-st);
            st = i;
        }
    }
    debug(pre, suf);

    return pii(pre, suf);
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    int pre, suf;
    REP (st, n) {
        cin >> p;
        if (st == 0) {
            tie(pre, suf) = build();
            hd = p[0];
            tl = p[SZ(p)-1];
        } else {
            int pp, ps;
            tie(pp, ps) = build();
            if (pp == SZ(p) && p[0] == hd) {
                pre = pp * (pre + 1) + pre;
            } else {
                hd = p[0];
                pre = pp;
            }

            if (ps == SZ(p) && p[SZ(p)-1] == tl) {
                suf = ps * (suf + 1) + suf;
            } else {
                tl = p[SZ(p)-1];
                suf = pp;
            }

            if (pp == SZ(p)) {
                cur[hd-'a'] = max((lst[hd-'a'] + 1) * pp + lst[hd-'a'], cur[hd-'a']);
            } else {
                if (lst[hd-'a'] > 0) {
                    cur[hd-'a'] = max(cur[hd-'a'], pp+1);
                    cur[tl-'a'] = max(cur[tl-'a'], ps+1);
                    if (hd == tl) {
                        cur[hd-'a'] = max(cur[hd-'a'], pp+ps+1);
                    }
                }
            }

        }
        REP (i, 26) {
            if (lst[i]) {
                cur[i] = max(cur[i], 1);
            }
        }
        REP (i, 26) {
            lst[i] = cur[i];
        }
        pary(cur, cur + 26);
    }

    int ans = 0;
    REP (i, 26) {
        ans = max(ans, cur[i]);
    }

    cout << ans << endl;
    return 0;
}
