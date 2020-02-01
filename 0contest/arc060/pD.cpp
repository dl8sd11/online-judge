#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
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
#define TIME(i) Timer i(#i)
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
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 500005;

string w;
int n;
int z_pre[MAXN], z_suf[MAXN];
// bool g_pre[MAXN], g_suf[MAXN];

void build_z (int *z, string s) {
    z[0] = 0;
    int bst = 0;
    REP1 (i, n-1) {
        if (z[bst] + bst <= i) {
            z[i] = 0;
        } else {
            z[i] = min(z[bst] + bst - i, z[i - bst]);
        }
        while (i+z[i]<n && s[i+z[i]] == s[z[i]]) {
            z[i]++;
        }
        if (i + z[i] >= bst + z[bst]) {
            bst = i;
        }
    }
}

vector<int> divi[MAXN];
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();

    cin >> w;
    n = SZ(w);
    if (equal(w.begin() + 1, w.end(), w.begin())) {
        cout << n << endl;
        cout << 1 << endl;
    } else {
        string rev = w;
        reverse(ALL(w));

        build_z(z_pre, w);
        build_z(z_suf, rev);
        reverse(z_suf, z_suf+n);
        
        pary(z_pre, z_pre + n);
        pary(z_suf, z_suf + n);

        bool flag = false;
        REP1 (i, n-1) {
            if (n % i == 0 && i+z_pre[i] == n) {
                flag = true;
            }
        }

        if (flag) {
            for (int i=1; i<=n; i++) {
                for (int j=i*2; j<=n; j+=i) {
                    divi[j].eb(i);
                }
            }

            int ans = 0;
            REP (i, n-1) {
                bool good = true;
                for (auto d : divi[i+1]) {
                    if (i == 2 && z_pre[d]+d >= i+1) {
                        debug(d);
                    }
                    good &= z_pre[d]+d < i+1;
                }
                for (auto d : divi[n-i-1]) {
                    if (i == 2 && z_suf[n-d-1]+d >= n-i-1) {
                        debug(d);
                    }
                    good &= z_suf[n-d-1]+d < n-i-1;
                }
                ans += good;
                debug(i, good);
            }

            cout << 2 << endl;
            cout << ans << endl;
        } else {
            cout << 1 << endl;
            cout << 1 << endl;
        }
    }

    return 0;
}
