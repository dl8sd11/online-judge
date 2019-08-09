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

int n, q, c, a[MAXN];

struct Query {
    int type;
    int l, r, k, tm;
};
vector<Query> query;
vector<pii> ans;

int trL[MAXN * 4], trR[MAXN * 4], trMx[MAXN * 4], len[MAXN * 4];

void pull (int o) {
    trL[o] = max(trL[o<<1], trMx[o<<1] == len[o<<1] ? len[o<<1] + trL[o<<1|1] : 0);
    trR[o] = max(trR[o<<1|1], trMx[o<<1|1] == len[o<<1|1] ? len[o<<1|1] + trR[o<<1] : 0);
    trMx[o] = max({trMx[o<<1], trMx[o<<1|1], trR[o<<1] + trL[o<<1|1]});
}

void build (int o, int l, int r) {
    if (r == l + 1) {
        trMx[o] = len[o] = trL[o] = trR[o] = 1;
    } else {
        int mid = (l + r) >> 1;
        len[o] = r - l;
        build(o<<1, l, mid);
        build(o<<1|1, mid, r);
        pull(o);
    }
}

void chg (int o, int nL, int nR, int pos, bool state) {
    debug(nL, nR, pos, state);
    if (pos == nL && pos == nR - 1) {
        trMx[o] = trL[o] = trR[o] = !state;
    } else {
        int mid = (nL + nR) >> 1;
        if (pos >= mid) {
            chg(o<<1|1, mid, nR, pos, state);
        } else {
            chg(o<<1, nL, mid, pos, state);
        }
        pull(o);
    }
}

array<int, 4> empt = {0, 0, 0, 0};
array<int, 4> qry (int o, int nL, int nR, int qL, int qR) {
    if (nL >= qR || nR <= qL || qL >= qR) {
        return empt;
    } else if (nL >= qL && nR <= qR) {
        return {trL[o], trR[o], trMx[o], len[o]};
    } else {
        int mid = (nL + nR) >> 1;
        array<int, 4> rL = qry(o<<1, nL, mid, qL, qR), rR = qry(o<<1|1, mid, nR, qL, qR);
        if (rL == empt) {
            return rR;
        } else if (rR == empt) {
            return rL;
        } else {
            array<int, 4> ret;
            ret[3] = rL[3] + rR[3];
            ret[0] = max(rL[0], rL[2] == rL[3] ? rL[3] + rR[0] : 0);
            ret[1] = max(rR[1], rR[2] == rR[3] ? rR[3] + rL[1] : 0);
            ret[2] = max({rL[2], rR[2], rL[1] + rR[0]});
            return ret;

        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> q >> c;
    REP (i, n) {
        cin >> a[i];
        query.pb({0, i, i+1, a[i], 0});
    }
    build(1, 0, n);

    REP1 (i, q) {
        int cmd;
        cin >> cmd;
        if (cmd == 0) {
            int p, k;
            cin >> p >> k;
            query.pb({2, p, p+1, a[p], i});
            query.pb({0, p, p+1, k, i});
            a[p] = k;
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            query.pb({1, l, r, k, i});
        }
    }

    sort(ALL(query), [&](Query q1, Query q2) {
        if (q1.k != q2.k) {
            return q1.k < q2.k;
        } else {
            return q1.tm < q2.tm;
        }
    });

    pary(trMx, trMx + n*2);
    REP (i, SZ(query)) {
        int hd = i;
        vector<int> pos;
        while (i < SZ(query) && query[i].k == query[hd].k) {
            auto Q = query[i];
            debug( Q.type, Q.l, Q.r, Q.k);
            if (Q.type == 1) {
                ans.eb(Q.tm, qry(1, 0, n, Q.l, Q.r)[2]);
            } else {
                chg(1, 0, n, Q.l, Q.type ? 0 : 1);
                if (Q.type == 0) {
                    pos.eb(Q.l);
                }
            }
            pary(len, len + n*2);
            pary(trMx, trMx + n*2);
            pary(trL, trL + n*2);
            pary(trR, trR + n*2);
            i++;
        }

        for (auto p : pos) {
            chg(1, 0, n, p, 0);
        }
        i--;
    }

    sort(ALL(ans));

    for (auto elm : ans) {
        cout << elm.Y << endl;
    }
    return 0;
}
