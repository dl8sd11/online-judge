#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
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

int t, n;
string s;

pii mrg (pii p1, pii p2) {
    return pii(min(p1.X, p2.X), max(p1.Y, p2.Y));
}

struct RMQ {
    pii pre[MAXN], suf[MAXN], a[MAXN];
    RMQ() {}
    pii add (pii p1, int val) {
        return pii(p1.X + val, p1.Y + val);
    }

    int len (int i, int val) {
        pii ret = mrg(pre[i-1], add(suf[i], val));
        ret = mrg(ret, add(a[i-1], val));
        // debug(pre[i-1], add(suf[i], val), add(a[i-1],val));
        return ret.Y - ret.X + 1;
    }
}hori, vert;

/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();
    cin >> t;
    while (t--) {
        cin >> s;
        n = SZ(s) + 1;

        int x = 0, y = 0;

        hori.pre[0] = vert.pre[0] = {0, 0};
        hori.suf[n] = vert.suf[n] = {iNF, -iNF};
        REP1 (i, n-1) {
            if (s[i-1] == 'W') {
                y++;
            } else if (s[i-1] == 'S') {
                y--;
            } else if (s[i-1] == 'A') {
                x--;
            } else if (s[i-1] == 'D') {
                x++;
            }
            hori.a[i] = pii(x, x);
            vert.a[i] = pii(y, y);

            hori.pre[i] = mrg(hori.pre[i-1], hori.a[i]);
            vert.pre[i] = mrg(vert.pre[i-1], vert.a[i]);
        }

        for (int i=n-1; i >= 0; i--) {
            hori.suf[i] = mrg(hori.suf[i+1], hori.a[i]);
            vert.suf[i] = mrg(vert.suf[i+1], vert.a[i]);
        }

        int wid_o = hori.len(n-1, 0), hei_o = vert.len(n-1, 0);
        int wid_c = iNF, hei_c = iNF;
        REP1 (i, n-1) {
            wid_c = min(wid_c, hori.len(i, 1));
            wid_c = min(wid_c, hori.len(i, -1));
 
            hei_c = min(hei_c, vert.len(i, -1));
            hei_c = min(hei_c, vert.len(i, 1));
        }

        debug(wid_o, hei_o, wid_c, hei_c);

        cout << min({ll(wid_o) * hei_o, ll(wid_c) * hei_o, ll(wid_o) * hei_c}) << endl;
    }
    return 0;
}
