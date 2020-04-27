#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
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
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;


vector<char> make (int n, int m) {
    vector<char> res;

    for (int i=0; i<n*m; i++) {
        res.emplace_back('.');
    }

    for (int i=1; i<n; i+=2) {
        for (int j=0; j<m; j++) {
            res[i*m + j] = '#';
        }
        if ((i/2) & 1) {
            res[i*m + m-1] = '.';
        } else {
            res[i*m] = '.';
        }
    }

    res[m-1] = 'x';
    
    if ((n/2) & 1) {
        res[n*m-1] = 'o';
    } else {
        res[(n-1)*m] = 'o';
    }
    
    return res;
}

void print (vector<char> v, int n, int m) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cout << v[i*m+j];
        }
        cout << endl;
    }

    cout << "$$$$$$$$$$$$$$$$$$$" << endl;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    int n, t, m;
    cin >> t;
    while (t--) {
        int d;
        cin >> n >> m >> d;

        vector<char> res1 = make(m, n);
        vector<char> res2 = make(n, m);



        int cnt1 = 0, cnt2 = 0;
        for (int i=0; i<n*m; i++) {
            cnt1 += res1[i] == '#';
            cnt2 += res2[i] == '#';
        }
        vector<char> res = (cnt1 < cnt2 ? res1 : res2);


        d--;
        for (int i=0; i<n*m; i++) {
            if (res[i] == '.' && (d--) > 0) {
                res[i] = 'o';
            }
        }
        d = max(0, d);

        if (cnt1 < cnt2) {

           for (int i=0; i<n; i++) {
               for (int j=0; j<m; j++) {
                   cout << res[i+j*n];
               }
               cout << endl;
           }
        } else {
            // return 0;
            for (int i=0; i<n; i++) {
                for (int j=0; j<m; j++) {
                    cout << res[i*m+j];
                }
                cout << endl;
            }
        }

        if (t) {
            cout << endl;
        } 
    }
}

