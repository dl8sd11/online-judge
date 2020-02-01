#include <bits/stdc++.h>
using namespace std;
typedef  int ll;
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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f;
const ll MAXN=3e5+5;
const ll MAXLG=__lg(MAXN)+2;

int n,k,sft;
deque<pii> qu[MAXN];
int dp[MAXN],pos[MAXN],zero;
bool c[MAXN];

int t[MAXN*2],N;
void build(){
    for(int i=MAXN-1;i>0;i--)t[i] = min(t[i<<1],t[i<<1|1]);
}
void modi(int x,int y){
    x += sft;
    for(t[x+=MAXN]=y;x>1;x>>=1)t[x>>1] = min(t[x],t[x^1]);
}
int query(int l,int r){
    int res = INF;
    l += sft;
    r += sft;
    for(l+=MAXN,r+=MAXN;l<r;l>>=1,r>>=1){
        if(l&1)res=min(res,t[l++]);
        if(r&1)res=min(res,t[--r]);
    }
    return res;
}
/********** Good Luck :) **********/
int main()
{
    // IOS();
#ifndef tmd
    freopen("redistricting.in","r",stdin);
    freopen ("redistricting.out","w",stdout);
#endif
    cin >> n >> k;

    MEM(t,INF);
    N = n;
    sft = -INF;
    int sum = 0;
    REP (i,n) {
        char inp;
        cin >> inp;
        c[i] = inp=='H';
        sum += c[i]?1:-1;
        sft = max(sft,sum);
    }
    sft++;
    debug(sft);
    build();
    REP (i,n) {
        // debug(i);
        pos[i] = zero;
        zero -= c[i]?1:-1;

        if (i-k>=0) {
            while(qu[sft+pos[i-k]].size()&&qu[sft+pos[i-k]].front().X == i-k) {
                qu[sft+pos[i-k]].pop_front();
            }
            if (qu[sft+pos[i-k]].empty()) {
                modi(pos[i-k],INF);
            } else {
                modi(pos[i-k],qu[sft+pos[i-k]].front().Y);
            }
        }

        while (qu[sft+pos[i]].size()&&qu[sft+pos[i]].back().Y >= dp[i-1])qu[sft+pos[i]].pop_back();
        qu[sft+pos[i]].emplace_back(i,i?dp[i-1]:0);
        modi(pos[i],qu[sft+pos[i]].front().Y);

        debug(query(zero+1,MAXN-sft),query(-sft,zero+1)+1);
        dp[i] = min(query(zero+1,MAXN-sft),query(-sft,zero+1)+1);
    }

    pary(dp,dp+n);
    cout << dp[n-1] << endl;
    return 0;
}
