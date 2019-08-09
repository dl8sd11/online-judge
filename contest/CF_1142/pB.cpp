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
const ll MAXN = 200005;
const ll MAXLG = __lg(MAXN) + 3;


int n, m, q, nxt[MAXLG][MAXN], lst[MAXN], p[MAXN], a[MAXN], pos[MAXN], mat[MAXN * 2];

void build () {
    for (int i=m-1; i>0; i--) {
        mat[i] = min(mat[i<<1], mat[i<<1|1]);
    }
}

int qry (int l, int r) {
    int ret = iNF;
    for (l+=m, r+=m; l < r; l>>=1, r>>=1) {
        if (l&1) {
            ret = min(ret, mat[l++]);
        }
        if (r&1) {
            ret = min(ret, mat[--r]);
        }
    }
    return ret;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m >> q;
    REP (i, n) {
        cin >> p[i];
        pos[p[i]] = i;
    }
    REP (i, m) {
        cin >> a[i];
    }

    MEM(nxt, iNF);
    MEM(lst, iNF);
    RREP (i, m-1) {
        nxt[0][i] = lst[p[(pos[a[i]] + 1) % n]];
        lst[a[i]] = i;
    }

    REP1 (i, MAXLG - 1) {
        REP (j, m) {
            nxt[i][j] = nxt[i-1][j] == iNF ? iNF : nxt[i-1][nxt[i-1][j]];
        }
    }

    REP (i, m) {
        int cur = i;
        REP (j, MAXLG) {
            if ((1<<j) & (n-1)) {
                cur = nxt[j][cur];
                if (cur == iNF) {
                    break;
                }
            }
        }
        mat[i + m] = cur;
        debug(i, cur);
    }

    build();
    pary(mat, mat+m*2);

    while (q--) {
        int l, r;
        cin >> l >> r;
    
        int lft = qry(l-1, r);
        // debug(lft);
        cout << (lft <= r-1);
    }
    cout << endl;
    return 0;
}
