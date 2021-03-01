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
const ll MAXN = 30000;

ll n;
struct Event {
    ll x,y,z,type,id;
}event[MAXN*2];
#ifdef tmd
ostream& operator << (ostream &_s,const Event &q){return _s<<"("<<q.x<<","<<q.y<<","<<q.z<<")"<<q.type<<","<<q.id;}
#endif
ll ans[MAXN],bit[MAXN];
void add(ll pos,ll val) {
    for (;pos<MAXN;pos+=-pos&pos) {
        bit[pos] += val;
    }
}

ll qry(ll pos) {
    ll ret = 0;
    for (;pos>=1;pos-=-pos&pos) {
        ret += bit[pos];
    }
    return ret;
}

void solve(vector<ll> V,ll L,ll R) {
    if (L < R - 1) {
        vector<ll> lV,rV;
        ll mid = (L + R) >> 1;
        for (auto v : V) {
            if (event[v].x < mid) {
                lV.eb(v);
            } else {
                rV.eb(v);
            }
        }
        ll rptr = 0;
        for (auto l : lV) {
            while (rptr < SZ(rV) && event[rV[rptr]].z > event[l].z) {
                if (event[rV[rptr]].type == 1) {
                    add(event[rV[rptr]].y,1);
                }
                rptr++;
            }
            if (event[l].type == 0) {
                ans[event[l].id] += qry(MAXN-1) - qry(event[l].y);
            }
        }

        REP (i,rptr) {
            if (event[rV[i]].type == 1) {
                add(event[rV[i]].y,-1);
            }
        }
        solve(lV,L,mid);
        solve(rV,mid,R);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        ll x,y,z;
        cin >> x >> y >> z;
        event[i*2] = {x,y,z,1,i};
        event[i*2+1] = {x,y,z,0,i};
    }

    sort(event,event+n*2,[&](Event e1,Event e2){return e1.z > e2.z;});

    vector<ll> id;
    REP (i,n*2) {
        id.eb(i);
    }
    solve(id,0,MAXN+1);

    REP (i,n) {
        cout << ans[i] << endl;
    }
    return 0;
}
