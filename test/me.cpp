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

ll t, n, q, s;
set<pii> del;

void chg(ll pos) {
    if (del.empty()) {
        del.insert({pos, pos});
        return;
    }
    ll l = pos, r = pos;
    auto ptrR = del.lower_bound(pii(pos,-1));
    auto ptrL = ptrR;
    if (ptrR != del.begin()) {
        ptrL = prev(ptrR);
        if (ptrL->Y >= pos) {
            return;
        } else if (ptrL->Y == pos-1) {
            l = ptrL->X;
            del.erase(ptrL);
        }
    }

    if (ptrR != del.end()) {
        if (ptrR->X == pos) {
            return;
        } else if (ptrR->X == pos+1) {
            r = ptrR->Y;
            del.erase(ptrR);
        }
    } 

    del.insert({l, r});
}

ll qry(ll l, ll r) {
    if (del.empty()) {
        return r;
    }
    auto ptr = del.lower_bound({r+1,-1});
    if (ptr != del.begin()) {
        ptr = prev(ptr);
        if (ptr->Y < r) {
            return r;
        } else if (ptr->X <= l) {
            return 0;
        } else {
            return ptr->X - 1;
        }
    } else {
        return r;
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
        del.clear();
        s = 0;
        cin >> n >> q;
        while (q--) {
            ll cmd, x, l, r;
            cin >> cmd;
            if (cmd == 1) {
                cin >> x;
                chg(x+s);
                debug(del);
            } else {
                cin >> l >> r;
                ll res = qry(l+s, r+s);
                cout << res << endl;
                s = (s + res) % n;
            }
        }
    }
    return 0;
}
