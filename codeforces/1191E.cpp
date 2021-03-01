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
const ll MAXN = 100005;

int n, k;
bool a[2][MAXN];

bool win(int s) {
    int l = n + 1, r = -1;
    REP (i, n) {
        if (a[s][i]) {
            l = min(l, i);
            r = i;
        }
    }
    return r - l + 1 <= k;
}

bool every(int s) {
    deque<int> l, m, r;
    bool lose = true;
    REP (i, n) {
        if (a[s][i]) {
            if (i < k) {
                m.eb(i);
            } else {
                r.eb(i);
            }
        }
    }
    for (int i=k; i<= n; i++) {
        if (SZ(l) && SZ(r)) {
            lose = false;
        } else if (SZ(l)) {
            if (l.back() - l.front() + 1 > k) {
                lose = false;
            }
        } else if (SZ(r)) {
            if (r.back() - r.front() + 1 > k) {
                lose = false;
            }
        }
        if (i < n) {
            if (a[s][i]) {
                r.pop_front();
                m.eb(i);
            }
            if (a[s][i-k]) {
                m.pop_front();
                l.eb(i-s);
            }
        }
    }
    return lose;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> k;
    REP (i, n) {
        char c;
        cin >> c;
        a[0][i] = c == '0';
        a[1][i] = c == '1';
    }

    if (win(0) || win(1)) {
        cout << "tokitsukaze" << endl;
    } else if (every(0) && every(1)){
        cout << "quailty" << endl;
    } else {
        cout << "once again" << endl;
    }
    return 0;
}
