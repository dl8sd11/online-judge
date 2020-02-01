#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef pair<ll,ll> pii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define SZ(i) ll(i.size())
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#endif
const ll MAXN = 1024;
ll q,n,m,a,b;
bool ink[MAXN][MAXN];
pii inkv[MAXN*MAXN],pat[MAXN*MAXN];
ll inkcnt,patcnt;
char c[MAXN];
int main () {
    IOS();
    cin >> q;
    while (q--) {
        inkcnt = 0;
        patcnt = 0;
        cin >> n >> m >> a >> b;
        REP (i,n) {
            cin >> c;
            REP (j,m) {
                if (c[j] == 'x') {
                    ink[i][j] = true;
                    inkv[inkcnt].X = i;
                    inkv[inkcnt++].Y = j;
                } else {
                    ink[i][j] = false;
                }
            }
        }
        
        REP (i,a) {
            cin >> c;
            REP (j,b) {
                if (c[j] == 'x') {
                    pat[patcnt].X = i;
                    pat[patcnt++].Y = j;
                }
            }
        }
        
        bool ans = true;
        
        REP (j,inkcnt) {
            pii pos = inkv[j];
            if (!ink[pos.X][pos.Y]) {
                continue;
            }
            REP (i,patcnt) {
                pii cur = {pos.X+pat[i].X-pat[0].X,pos.Y+pat[i].Y-pat[0].Y};
                if ((cur.X < 0) || (cur.X >= n) || (cur.Y < 0) || (cur.Y >= m)) {
                    ans = false;
                    break;
                } else if (!ink[cur.X][cur.Y]) {
                    ans = false;
                    break;
                } else {
                    ink[cur.X][cur.Y] = false;
                }
            }
            if (!ans) {
                break;
            }
        }
        if (ans) {
            cout << "TAK" << endl;
        } else {
            cout << "NIE" << endl;
        }
    }
}