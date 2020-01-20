#include <bits/stdc++.h>
#pragma GCC optimize("O3","unroll-loops")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define X first
#define Y second
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> ostream &operator << (ostream &os,pair<T,T> &v){return os<<"{"<<v.X<<","<<v.Y<<"}";}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif


const int MAXN = 1001;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int q, n, m, a, b;
bool doc[MAXN][MAXN];


vector<pii> seal;

void operator -= (pii &p1, const pii &p2) {
    p1.X -= p2.X;
    p1.Y -= p2.Y;
}

inline bool valid (int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    scanf("%d\n",&q);

    while (q--) {
        scanf("%d %d %d %d\n",&n,&m,&a,&b);
        seal.clear();

        int cnt = 0;
        REP (i, n) {
            REP (j, m) {
                char c = getchar();
                debug(c);

                doc[i][j] = c == 'x';
                cnt += doc[i][j];
            }
            getchar();
        }

        REP (i, a) {
            REP (j, b) {
                char c = getchar();
                if (c == 'x') {
                    seal.emplace_back(i, j);
                }
            }
            getchar();
        }

        for (int i=SZ(seal)-1;i>=0;i--) {
            seal[i] -= seal[0];
        }

        bool fail = false;
        int x, y;
        REP (i, n) {
            REP (j, m) {
                if (!fail && doc[i][j]) {
                    for (auto pos : seal) {
                        x = i + pos.X;
                        y = j + pos.Y;

                        if (!valid(x,y) || !doc[x][y]) {
                            fail = true;
                            break;
                        } else {
                            doc[x][y] = false;
                            cnt--;
                        }

                    }
                }
            }
        }

        puts(!fail && cnt == 0 ? "TAK" : "NIE");
    }
}

/*
2
3 4 4 2
xx..
.xx.
xx..
x.
.x
x.
..
2 2 2 2
xx
xx
.x
x.
*/
