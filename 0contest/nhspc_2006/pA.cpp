#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define eb emplace_back
#define MEM(a,b) memset(a,(b),sizeof(a))
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
/*********Good***Luck*********/
int main () {
    IOS();
    cin >> n;

    double sum = 0;
    REP (i, n) {
        REP (j, n) {
            double R, G, B, X, Y, Z;
            cin >> R >> G >> B;
            X = 0.5149 * R + 0.3244 * G + 0.1607 * B;
            Y = 0.2654 * R + 0.6704 * G + 0.0642 * B;
            Z = 0.0248 * R + 0.1248 * G + 0.8504 * B;

            sum += Y;

            cout << fixed << setprecision(4) << X << " ";
            cout << fixed << setprecision(4) << Y << " ";
            cout << fixed << setprecision(4) << Z << endl;
        }
    }

    cout << "The average of Y is " << fixed << setprecision(4) << sum / n / n << endl;
    return 0;
}
