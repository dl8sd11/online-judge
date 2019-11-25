#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 500005;
const ll MOD = 1000000007;

int n, m, k, cnt;
bool vis[31][31];
map<string, int> id;
pair<int,int> pos[2003];
/*********************GoodLuck***********************/
int main () {
    IOS();
#ifndef tmd
    freopen("input.txt","r",stdin);
    freopen("output.txt", "w", stdout);
#endif

    cin >> n >> m >> k;
    while (k--) {
        string cmd, name;
        int x, y;
        cin >> cmd;
        if (cmd[0] == '+') {
            cin >> x >> y;
            cin >> name;
            debug(name, x, y);
            id[name] = cnt++;

            bool fnd = false;
            for (int i=x; i<=n; i++) {
                for (int j=y;j<=m; j++) {
                    if (!vis[i][j]) {
                        pos[id[name]] = {i, j};
                        vis[i][j] = true;
                        debug(name, i, j);
                        fnd = true;
                        break;
                    }
                }
                if (fnd) {
                    break;
                }
                y = 1;
            }

            if (!fnd) {
                id.erase(name);
            }
        } else {
            cin >> name;
            if (id.count(name)) {
                pair<int,int> cur = pos[id[name]];
                id.erase(name);
                vis[cur.first][cur.second] = false;
                cout << cur.first << " " << cur.second << endl;
            } else {
                cout << -1 << " " << -1 << endl;
            }
        }

    }


}
