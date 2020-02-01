#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define eb emplace_back
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#endif

const int iNF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 10004;

typedef pair<ll,int> pli;

bool dp[3][MAXN];
int stp[3][MAXN];

int main () {
    IOS();

    int x, y;
    cin >> x >> y;

    #define d(i,j,k) dp[(i+3-k)%3][j+1]
    #define s(i,j,k) stp[(i+3-k)%3][j+1]
    REP1 (i, x) {
        REP1 (j, y) {
            if (!d(i,j-2,1) && !d(i,j-1,2)) {
                d(i,j,0) = true;
                s(i,j,0) = max(s(i,j-2,1),s(i,j-1,2))+1;
            } else {
                d(i,j,0) = false;
                if (d(i,j-2,1) && d(i,j-1,2)) {
                    s(i,j,0) = min(s(i,j-2,1),s(i,j-1,2))+1;
                } else if (d(i,j-2,1)) {
                    s(i,j,0) = s(i,j-2,1)+1;
                } else {
                    s(i,j,0) = s(i,j-1,2)+1;
                }
            }
        }
    }


    if (d(x,y,0)) {
        cout << "Lose " << s(x,y,0)-1 << endl;
    } else {
        cout << "Win " << s(x,y,0)-1 << endl;
    }

}
