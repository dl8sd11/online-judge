#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
typedef pair<ll, ll> pi;
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
const ll MAXN = ll(1e5)+7;
pair<ll,ll> data[MAXN];
ll tran[MAXN];
ll BIT[MAXN];
void add(ll pos) {
	while (pos<=MAXN) {
		BIT[pos]++;
		pos += (-pos)&pos;
	}
}
ll  query(ll pos) {
	ll ret = 0;
	while (pos>=1) {
		ret += BIT[pos];
		pos-=(-pos)&pos;
	}
	return ret;
}
/********** Main()  function **********/
int main()
{
		ll n,num=0;
		while (cin>>n&&n) {
			MEM(BIT,0);

			REP1 (i,n) {
				cin>>data[i].X;
				data[i].Y=i;
			}
      sort(data+1,data+n+1);
			tran[data[1].Y]=1;
			ll idx = 1;
			for (ll i=2;i<=n;i++) {
				tran[data[i].Y] = (data[i].X==data[i-1].X)?idx:++idx;
			}
			ll ans = 0;
			REP1 (i,n) {
				add(tran[i]);
				ans+=i-query(tran[i]);
			}
			cout<<"Case #"<<++num<<": "<<ans<<endl;
		}
}
