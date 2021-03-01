#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
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
const int INF = 0x3f3f3f3f;
const ll MAXN = 501;

int n;
ll a[MAXN],b[MAXN],k[MAXN];
ll g[MAXN][MAXN],lx[MAXN],ly[MAXN],slack_y[MAXN];
int px[MAXN],py[MAXN],match_y[MAXN],par[MAXN];

void adjust(int y){//把增廣路上所有邊反轉 
	match_y[y]=py[y];
	if(px[match_y[y]]!=-2)
		adjust(px[match_y[y]]);
}
bool dfs(int x){//DFS找增廣路 
	for(int y=0;y<n;++y){
		if(py[y]!=-1)continue;
		ll t=lx[x]+ly[y]-g[x][y];
		if(t==0){
			py[y]=x;
			if(match_y[y]==-1){
				adjust(y);
				return 1;
			}
			if(px[match_y[y]]!=-1)continue;
			px[match_y[y]]=y;
			if(dfs(match_y[y]))return 1;
		}else if(slack_y[y]>t){ 
			slack_y[y]=t;
			par[y]=x;
		}
	}
	return 0;
}
inline ll km(){
	memset(ly,0,sizeof(int)*n);
	memset(match_y,-1,sizeof(int)*n);
	for(int x=0;x<n;++x){
		lx[x]=-INF;
		for(int y=0;y<n;++y){
			lx[x]=max(lx[x],g[x][y]);
		}
	}
	for(int x=0;x<n;++x){
		for(int y=0;y<n;++y)slack_y[y]=INF;
		memset(px,-1,sizeof(int)*n);
		memset(py,-1,sizeof(int)*n);
		px[x]=-2;
		if(dfs(x))continue;
		bool flag=1;
		while(flag){
			ll cut=INF;
			for(int y=0;y<n;++y)
				if(py[y]==-1&&cut>slack_y[y])cut=slack_y[y];
			for(int j=0;j<n;++j){
				if(px[j]!=-1)lx[j]-=cut;
				if(py[j]!=-1)ly[j]+=cut;
				else slack_y[j]-=cut;
			}
			for(int y=0;y<n;++y){
				if(py[y]==-1&&slack_y[y]==0){
					py[y]=par[y];
					if(match_y[y]==-1){
						adjust(y);
						flag=0;
						break;
					}
					px[match_y[y]]=y;
					if(dfs(match_y[y])){
						flag=0;
						break;
					}
				}
			}
		}
	}
	ll ans=0;
	for(int y=0;y<n;++y)if(g[match_y[y]][y]!=-INF)ans+=g[match_y[y]][y];
	return ans;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> a[i] >> b[i] >> k[i];
    }

    REP (i,n) {
        REP (j,n) {
            g[i][j] = max(g[i][j],a[i]-b[i]*min(ll(j),k[i]));
        }
    }


    cout << km() << endl;
    return 0;
}
