#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<int, ll> pli;
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
const ll MAXN = 3003;

int n;
string w1[MAXN], w2[MAXN];
string s, t;
int l[MAXN], r[MAXN], z[MAXN];

int srch (string ss, const string &s2) {
    int sz1 = SZ(s), sz2 = SZ(s2);
    ss = ss + '@' + s2;
    z[0] = 0;
    int bst = 0;
    REP1 (i, SZ(ss) - 1) {
        if (z[bst] + bst >= i) {
            z[i] = min(z[i-bst], z[bst]+bst-i);
        } else {
            z[i] = 0;
        }
        while (i+z[i] < SZ(ss) && ss[z[i]] == ss[i+z[i]]) {
            z[i]++;
        }
        if (i + z[i] > bst + z[bst]) {
            bst = i;
        }
    }

    debug(ss);
    pary(z, z+sz1+sz2);
    REP1 (i, sz2) {
        if (z[i+sz1] == sz1) {
            return i-1;
        }
    }
    return sz2;
}

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;

    REP (i, n) {
        cin >> w1[i];
    }
    REP (i, n) {
        cin >> w2[i];
    }
    REP (i, n) {
        if (w1[0] == w2[0] && w1[i] != w2[i]) {
            swap(w1[0], w1[i]);
            swap(w2[0], w2[i]);
        }
    }
    bool ret = true;
    REP (i, n) {
        l[i] = SZ(w1[i]), r[i] = -1;
        REP (j, SZ(w1[i])) {
            if (w1[i][j] != w2[i][j]) {
                l[i] = min(l[i], j);
                r[i] = max(r[i], j);
            }
        }

        if (i && l[i] != SZ(w1[i])) {
            if (s != w1[i].substr(l[i], r[i]-l[i]+1)) {
                debug(i, s);
                ret = false;
            }
            if (t != w2[i].substr(l[i], r[i]-l[i]+1)) {
                debug(i, t);
                ret = false;
            }
        } else if (i == 0) {
            s = w1[i].substr(l[i], r[i]-l[i]+1);
            t = w2[i].substr(l[i], r[i]-l[i]+1);
        }
    }
    if (!ret) {
        cout << "NO" << endl;
        return 0;
    }

    debug(s, t);
    while (l[0] > 0) {
        bool flag = true;
        REP1 (i, n-1) {
            if (l[i] == SZ(w1[i])) {
                continue;
            }
            if (l[i] <= 0 || w1[i][l[i]-1] != w1[0][l[0]-1] || w2[i][l[i]-1] != w2[0][l[0]-1]) {
                flag = false;
            }
        }
        if (!flag) {
            break;
        }
        REP (i, n) {
            if (l[i] == SZ(w1[i])) {
                continue;
            }
            l[i]--;
        }
    }

    while (r[0] < SZ(w1[0])-1) {
        bool flag = true;
        REP1 (i, n-1) {
            if (r[i] == -1) {
                continue;
            }
            if (r[i] >= SZ(w1[i])-1 || w1[i][r[i]+1] != w1[0][r[0]+1] || w2[i][r[i]+1] != w2[0][r[0]+1]) {
                flag = false;
            }
        }
        if (!flag) {
            break;
        }
        REP (i, n) {
            if (r[i] == -1) {
                continue;
            }
            r[i]++;
        }
    }

    s = w1[0].substr(l[0], r[0]-l[0]+1);
    t = w2[0].substr(l[0], r[0]-l[0]+1);

    debug(s, t);
    REP (i, n) {
        int a = srch(s, w1[i]);
        debug(a);
        debug(i);
        if (srch(s, w1[i]) != l[i]) {
            cout << "NO" << endl;
            return 0;
        } 
    }

    cout << "YES" << endl;
    cout << s << endl;
    cout << t << endl;
    return 0;
}
