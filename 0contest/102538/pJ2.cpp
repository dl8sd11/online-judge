/*
from: http://sunmoon-template.blogspot.com
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

std::vector<int> G[MAXN];// 1-base
vector<int>eid[MAXN];
std::vector<int> bcc[MAXN];
int low[MAXN],vis[MAXN],Time;
int bcc_id[MAXN],bcc_cnt;// 1-base
bool is_cut[MAXN];//bcc_id is ndef if is_cut
int st[MAXN],top;
void dfs(int u,int pa=-1){
	int v,child=0;
	low[u]=vis[u]=++Time;
	st[top++]=u;
	for(size_t i=0;i<G[u].size();++i){
		if(!vis[v=G[u][i]]){
			dfs(v,u),++child;
			low[u]=std::min(low[u],low[v]);
			if(vis[u]<=low[v]){
				is_cut[u]=1;
				bcc[++bcc_cnt].clear();
				int t;
				do{
					bcc_id[t=st[--top]]=bcc_cnt;
					bcc[bcc_cnt].push_back(t);
				}while(t!=v);
				bcc_id[u]=bcc_cnt;
				bcc[bcc_cnt].push_back(u);
			}
		}else if(vis[v]<vis[u]&&v!=pa)//reverse 
			low[u]=std::min(low[u],vis[v]);
	}
	if(pa==-1&&child<2)is_cut[u]=0;//u for root
}
inline void bcc_init(int n){
	Time=bcc_cnt=top=0;
	for(int i=0;i<n;++i){
		G[i].clear();
		vis[i]=0;
		is_cut[i]=0;
		bcc_id[i]=0;
	}
}

#define pii pair<int, int>
int pa[MAXN];
int find(int x){return x == pa[x] ? x : pa[x] = find(pa[x]);}

int oino () {
    int n, m;
    cin >> n >> m;
    bcc_init(n);
    vector<pii> hi;
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v; --u; --v;
        G[u].emplace_back(v);
        eid[u].emplace_back(i);
        eid[v].emplace_back(i);
        G[v].emplace_back(u);
        hi.emplace_back(u,v);
    }

    for (int i = 0; i<n; ++i) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i<m; ++i) pa[i] = i;
    for (int i = 0; i<n; ++i) {
        if (!is_cut[i]) {
            for (int j : eid[i]) {
                pa[j] = 
            }
        }
    }
    
}

int main(){

    int t; cin>>t;
    while (t--) oino();
}