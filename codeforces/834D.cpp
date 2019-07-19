#pragma GCC optimize("O3")
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
const int iNF = 0x3f3f3f3f;
const ll MAXN = 35004;

int n, k, a[MAXN], dp[51][MAXN];

namespace Cost {
    struct Node {
        Node *lc, *rc;
        int val;
    };
    unordered_map<int,int> cache[MAXN];

    Node *build(int l, int r) {
        if (l == r - 1) {
            return new Node {0,0,0};
        } else {
            int m = (l + r) >> 1;
            return new Node{build(l,m), build(m,r), 0};
        }
    }
    Node *root[MAXN];

    int val(Node *nd) {
        return nd ? nd->val : 0;
    }
    int qry(int l, int r, int L, int R, Node *nd) {
        if (l == L && r == R) {
            return nd->val;
        }
        int m = (L + R) >> 1;
        if (l >= m) {
            return qry(l, r, m, R, nd->rc);
        } else if (r <= m) {
            return qry(l, r, L, m, nd->lc);
        } else {
            return qry(l, m, L, m, nd->lc) + qry(m, r, m, R, nd->rc);
        }
    }

    Node *add(int p, int L, int R, Node *nd) {
        Node *ret = new Node(*nd);
        ret->val++;
        if (L == p && R == p+1) {
            return ret;
        }
        int m = (L + R) >> 1;
        if (p >= m) {
            ret->rc = add(p, m, R, nd->rc);
        } else  {
            ret->lc = add(p, L, m, nd->lc);
        }
        return ret;
    }

    int val(int l, int r) {
        if (l > r) {
            return 0;
        }
        if (cache[l].find(r) == cache[l].end()) {
            cache[l][r] = qry(0, l, 0, MAXN, root[r]) - qry(0, l, 0, MAXN, root[l-1]);
        }
        return cache[l][r];
    }

    void make() {
        int prev[MAXN] = {};
        root[0] = build(0, MAXN);
        REP1 (i, n) {
            root[i] = add(prev[a[i]], 0, MAXN, root[i-1]);
            prev[a[i]] = i;
        }
    }

}
void solve(int i, int jL, int jR, int tL, int tR) {
    if (jL >= jR) {
        return;
    }
    // if (tR >= jL) {
    //     debug(i, jL, jR, tL, tR);
    // }
    if (tL == tR - 1) {
        for (int j=jL; j<jR; j++) {
            dp[i][j] = dp[i-1][tL] + Cost::val(tR, j);
        }
    } else {
        int tran = tL;
        int jM = (jL + jR) >> 1;
        for (int t=tL; t<min(jM, tR); t++) {
            int cur = dp[i-1][t] + Cost::val(t+1, jM);
            if (dp[i][jM] < cur) {
                dp[i][jM] = cur;
                tran = t;
            }
        }

        solve(i, jL, jM, tL, tran+1);
        solve(i, jM+1, jR, tran, tR);
    }
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> k;
    REP1 (i, n) {
        cin >> a[i];
    }
    Cost::make();

    REP1 (i, k) {
        solve(i, 0, n+1, 0, n+1);
    }

    cout << dp[k][n] << endl;
    return 0;
}
