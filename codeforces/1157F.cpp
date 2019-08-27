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
const ll MAXN = 200005;

int n, a[MAXN], cnt[MAXN], sum;

int ans;
pair<int, int> ansRng;
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();
    cin >> n;
    REP (i, n) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    int l = -1;
    REP1 (i, 200001) {
        if (cnt[i] >= 2) {
            sum += cnt[i];
            if (l == -1) {
                l = i;
            }
        } else {
            if (l != -1) {
                int cur = cnt[l-1] ? sum + 1 : sum;
                cur += cnt[i];
                if (cur > ans) {
                    ans = cur;
                    ansRng.X = cnt[l-1] ? l - 1 : l;
                    ansRng.Y = cnt[i] ? i : i - 1;
                }
            } else {
                int cur = cnt[i-1] + cnt[i];
                if (cur > ans) {
                    ans = cur;
                    ansRng.X = cnt[i-1] ? i - 1 : i;
                    ansRng.Y = cnt[i] ? i : i - 1;
                }
            }
            l = -1;
            sum = 0;
        }
    }
    
    debug(ans, ansRng);

    cout << ans << endl;

    vector<int> ansVec;
    for (int i=ansRng.X; i <= ansRng.Y; i++) {
        ansVec.eb(i);
        cnt[i]--;
    }

    for (int i=ansRng.Y; i >= ansRng.X; i--) {
        while (cnt[i]-- > 0) {
            ansVec.eb(i);
        }
    }

    debug(ansVec);
    assert(SZ(ansVec) == ans);
    REP (i, ans) {
        cout << ansVec[i] << " \n"[i==ans-1];
    }
    return 0;
}
