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
const ll MAXN = 100003;

ll n;
ll a[MAXN],b[MAXN];
ll bit[2][MAXN];
void add(ll pos,ll x,ll id) {
    pos++;
    for (;pos<MAXN;pos+=-pos&pos) {
        bit[id][pos] += x;
    }
}

ll query(ll pos,ll id) {
    pos++;
    ll ret = 0;
    for (;pos>=1;pos-=-pos&pos) {
        ret += bit[id][pos];
    }
    return ret;
}

vector<pii> cmd;
void opt(ll l,ll r,ll val) {
    for (ll i = l; i < r;i++) {
        a[l] += ((i&1) == (r&1) ? -val : val);
        a[r] += val;
        if (SZ(cmd) < 100000) {
            cmd.emplace_back(i+1,((i&1) == (r&1) ? -val : val));
        }
    }
}
inline bool valid(ll val) {
    return val >= 0 && val <= 9;
}
inline bool valid_r(ll val) {
    return val >= 1 && val <= 9;
}

ll find_odd(ll pos,ll op) {
    pos /= 2;
    ll L = -1,R = pos, sum = query(pos-1,pos&1);
    if (op > 0) {
        while (L < R - 1) {
            ll mid = (L+R)>>1;
            if (sum - query(mid-1,pos&1) < (pos-mid)*9) {
                L = mid;
            } else {
                R = mid;
            }
        }
    } else {
        while (L < R - 1) {
            ll mid = (L+R)>>1;
            if (sum - query(mid-1,pos&1) >= 0) {
                L = mid;
            } else {
                R = mid;
            }
        }
    }
    return L*2+1;
}
/*
9
123456789
123456789
*/
ll find_s(ll pos,ll op) {
    ll L = -1,R = pos, sum = query(pos-1,pos&1);

    
    return L;
    return -1;
}

ll find_n(ll pos,ll op) {
    ll L = -1,R = pos, sum = query(pos-1,(pos&1)^1);
    debug(pos,sum);
    if (op > 0) {
        while (L < R - 1) {
            ll mid = (L+R)>>1;
            debug(mid,query(mid-1,(pos&1)^1));
            if (sum - query(mid-1,(pos&1)^1) < (pos-mid+1)*9) {
                L = mid;
            } else {
                R = mid;
            }
        }
    } else {
        while (L < R - 1) {
            ll mid = (L+R)>>1;
            debug(mid,query(mid-1,(pos&1)^1));
            if (sum - query(mid-1,(pos&1)^1) >= 0) {
                L = mid;
            } else {
                R = mid;
            }
        }
    }
    return L;
    return -1;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        char c;
        cin >> c;
        a[i] = c - '0';
        add(i/2,a[i],i&1);
    }

    REP (i,n) {
        char c;
        cin >> c;
        b[i] = c - '0';
    }

    debug("shut up");
    ll x = find_odd(7,-1);
    debug(x);
    return 0;
    for (ll i=n-1;i>0;i--) {
        while (a[i] < b[i]) {
            ll mn = max(find_s(i,1),find_n(i,1));
            if (mn == -1) {
                cout << -1 << endl;
                return 0;
            }
            opt(mn,i,1);
        }
        while (a[i] > b[i]) {
            ll mn = max(find_s(i,-1),find_n(i,-1));
            if (mn == -1) {
                cout << -1 << endl;
                return 0;
            }
            opt(mn,i,-1);
        }
    }
    if (a[0] != b[0]) {
        cout << -1 << endl;
    } else {
        cout << SZ(cmd) << endl;
        for (auto md : cmd) {
            cout << md.X << " " << md.Y << endl;
        }
    }

    return 0;
}
