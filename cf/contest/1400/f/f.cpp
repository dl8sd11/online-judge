#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double, double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) static_cast<int>(i.size())
#define FOR(i, j, k, in) for (int i=j; i < (k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j; i >= (k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i, j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(), _a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
template<typename T, typename S>
istream &operator >> (istream &is, pair<T, S> &p) {
    return is >> p.X >> p.Y;
}
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do {\
    fprintf(stderr, "%s - %d (%s) = ", __PRETTY_FUNCTION__, __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T> void _do(T &&_x) {cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x, S &&..._t) {cerr <<_x <<" ,"; _do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s, const pair<_a, _b> &_p) {return _s << "(" << _p.X << "," << _p.Y << ")";}
template<typename It> ostream& _OUTC(ostream &_s, It _ita, It _itb)
{
    _s << "{";
    for (It _it=_ita; _it != _itb; _it++) {
        _s <<(_it == _ita?"":",")<< *_it;
    }
    _s << "}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s, const vector<_a> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _a, size_t _b> ostream &operator << (ostream &_s, const array<_a,_b> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const deque<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s, const map<_a,_b> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
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
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 2e5 + 5;


int x, res;

bool check (string str) {
    int sz = SZ(str);

    for (int i=0; i<sz; i++) {
        int s = 0;
        for (int j=i; j<sz; j++) {
            s += str[j] - '0';
            if (s != x && x % s == 0) return false;
        }
    }
    return true;
}

vector<string> bad;
void dfs (string vec, int sum) {
    if (sum >= x) {
        if (sum == x && check(vec)) {
            bad.eb(vec);
        }
    } else {
        for (int i=2; i<=9; i++) {
            vec.push_back(char(i+'0'));
            dfs(vec, sum+i);
            vec.pop_back();
        }        
    }
}

struct Trie {
    int go[10], link;
    bool isEnd;
    Trie() {
        memset(go, -1, sizeof(go));
        link = -1;
        isEnd = false;
    }
};
vector<Trie> trs(1);
void insert (string str) {
    int now = 0;
    for(char c : str) {
        c -= '0';
        if(trs[now].go[c] == -1) {
            trs[now].go[c] = trs.size();
            trs.emplace_back();
        }
        now = trs[now].go[c];
    }
    trs[now].isEnd = true;
}
void buildFail() {
    queue<int> q;
    for(int c = 0; c < 10; c++) {
        if(~trs[0].go[c]) {
            q.push(trs[0].go[c]);   
            trs[trs[0].go[c]].link = 0;
        }
    }
    while(!q.empty()) {
        int i = q.front(); q.pop();
        int L = trs[i].link;
        trs[i].isEnd |= trs[L].isEnd;
        for(int c = 0; c < 10; c++) {
            if(~trs[i].go[c]) {
                q.push(trs[i].go[c]);
                trs[trs[i].go[c]].link = trs[L].go[c];
            } else {
                trs[i].go[c] = trs[L].go[c];
            }
        }
    }
}

int dp[2][2341*10];

void cmin (int &x, int y) {
    x = min(x, y);
}
signed main () {
    TIME(main);
    IOS();

    string str;
    cin >> str >> x;

    if (x == 1) {
        bad.eb("1");
    } else {
        dfs("", 0); 
    }
    debug(bad.size());

    for (auto sub : bad) {
        insert(sub);
    }
    buildFail();
    

    MEM(dp, 0x3f);
    

    dp[1][0] = 0;
    for (int i=0; i<SZ(str); i++) {
        for (int j=0; j<SZ(trs); j++) {
            dp[i&1][j] = dp[i&1^1][j] + 1;
        }
        for (int j=0; j<SZ(trs); j++) {
            if (trs[j].go[str[i]-'0'] == -1) {
                cmin(dp[i&1][0], dp[i&1^1][j]);
            } else if (!trs[trs[j].go[str[i]-'0']].isEnd) {
                cmin(dp[i&1][trs[j].go[str[i]-'0']], dp[i&1^1][j]);
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for (int i=0; i<SZ(trs); i++) {
        cmin(ans, dp[SZ(str)&1^1][i]);
    }
    cout << ans << endl;

    return 0;
}


