#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define SZ(i) ll(i.size())
#define MEM(i,n) memset(i,(n),sizeof(i))
#define X first
#define Y second
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template <typename T> void _do(T &&x){cerr<<x<<endl;}
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 500003;
ll n,k,cc[MAXN],vis[MAXN],nxt[MAXN],vic,csiz[MAXN],dep[MAXN],ccnt,fat[MAXN];
ll cnum[MAXN];
void dfs1(ll nd) {
    vis[nd] = vic;
    ll x= nxt[nd];
    if (vis[x] == 0) {
        dfs1(x);
    } else if (vis[x] == vic) {
        ll beg = nd;
        ccnt++;
        ll num = 0;
        while (true) {
            cc[nd] = ccnt;
            csiz[ccnt]++;
            dep[nd] = 0;
            fat[nd] = nd;
            cnum[nd] = num++;
            if (nxt[nd] == beg) {
                break;
            }
            nd = nxt[nd];
        }
    }
}

void dfs2 (ll nd) {
    if (cc[nxt[nd]] == 0) {
        dfs2(nxt[nd]);
    }
    dep[nd] = dep[nxt[nd]] + 1;
    cc[nd] = cc[nxt[nd]];
    fat[nd] = fat[nxt[nd]];
}
const ll MAXLG = __lg(MAXN)+3;
ll anc[MAXLG][MAXN];

ll lca(ll u,ll v) {
    if (u == v) {
        return u;
    }
    if (dep[u] > dep[v]) {
        swap(u,v);
    }
    for (ll i=MAXLG-1;i>=0;i--) {
        if (dep[anc[i][v]] >= dep[u]) {
            v = anc[i][v];
        }
    }
    if (u == v) {
        return u;
    }
    for (ll i=MAXLG-1;i>=0;i--) {
        if (anc[i][u] != anc[i][v]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }
    return anc[0][u];
}

ll doc(ll f,ll t) {
    f = fat[f];
    t = fat[t];
    return (cnum[t]+csiz[cc[f]]-cnum[f])%csiz[cc[f]];
}

typedef pair<ll,ll> pii;
bool good(const pii &p1,const pii &p2) {
    if (max(p1.X,p1.Y) != max(p2.X,p2.Y)) {
        return max(p1.X,p1.Y) < max(p2.X,p2.Y);
    } else if (min(p1.X,p1.Y) != min(p2.X,p2.Y)) {
        return min(p1.X,p1.Y) < min(p2.X,p2.Y); 
    } else {
        return p1.X >= p1.Y;
    }
}
int main () {
    IOS();

    cin >> n >> k;
    REP1 (i,n) {
        cin >> nxt[i];
        anc[0][i]= nxt[i];
    }
    REP1 (i,MAXLG-1) {
        REP1 (j,n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
    REP1 (i,n) {
        vic++;
        dfs1(i);
    }
    REP1 (i,n) {
        if (cc[i] == 0) {
            dfs2(i);
        }
    }

#ifdef tmd
    REP1 (i,n) {
        cout << cc[i] << " \n"[i==n];
    }
    REP1 (i,n) {
        cout << dep[i] << " \n"[i==n];
    }
    REP1 (i,n) {
        cout << fat[i] << " \n"[i==n];
    }
#endif

    REP (i,k) {
        ll m,w;
        cin >> m >> w;
        if (cc[m] != cc[w]) {
            cout << "-1 -1" << endl;
        } else {
            if (fat[m] == fat[w]) {
                ll l = lca(m,w);
                cout << dep[m]-dep[l] << " " << dep[w]-dep[l] << endl;
            } else {
                ll dm = dep[m],dw = dep[w];
                pair<ll,ll> s1,s2;
                
                s1 = {dm+doc(m,w),dw};
                s2 = {dm,dw+doc(w,m)};
                if (good(s1,s2)) {
                    cout << s1.X << " " << s1.Y << endl;
                } else {
                    cout << s2.X << " " << s2.Y << endl;
                }
            }
        }
    }
}