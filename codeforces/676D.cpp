#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define REP(i,n) for(ll i=0;i<n;i++)

const ll MAXN = 1003;
ll n,m;
char input;
bool block[MAXN][MAXN][4];
pii st,tg;
priority_queue<pair<ll,pii>> pq;
struct stat{
	ll diss
};
void setblock(ll i,ll j,bool d0,bool d2,bool d3,bool d4) {
	block[i][j][0]=d0?1:0;
	block[i][j][1]=d1?1:0;
	block[i][j][2]=d2?1:0;
	block[i][j][3]=d3?1:0;
}
int main(){
	cin>>n>>m;
	REP(i,n) {
		REP(j,m) {
			cin>>tmp;
			if(tmp=='+') setblock(i,j,1,1,1,1);
			else if(tmp=='-') setblock(i,j,0,0,1,1);
			else if(tmp=='|') setblock(i,j,1,1,0,0);
			else if(tmp=='^') setblock(i,j,1,0,0,0);
			else if(tmp=='>') setblock(i,j,0,0,0,1);
			else if(tmp=='v') setblock(i,j,0,1,0,0);
			else if(tmp=='<') setblock(i,j,0,0,1,0);
			else if(tmp=='L') setblock(i,j,1,1,0,1);
			else if(tmp=='R') setblock(i,j,1,1,1,0);
			else if(tmp=='U') setblock(i,j,0,1,1,1);
			else if(tmp=='D') setblock(i,j,1,0,1,1);
			else if(tmp=='*') setblock(i,j,0,0,0,0);
		}
	}

	pq.push({0,st});

}
