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
const ll MAXN = 50004;


string pat;
int cnt;

bool valid () {
    bool flag = SZ(pat) & 1 ^ 1;
    int op = 0, qm = 0;
    for (auto c : pat) {
        if (c == '(') {
            op++;
        } else if (c == ')') {
            op--;
        } else {
            qm++;
            cnt++;
        }
        while (qm > 0 && qm > op) {
            qm--;
            op++;
        }
        if (op < 0) {
            flag = false;
            break;
        }

    }
    return flag && op == qm;
}

int a[MAXN], b[MAXN], s[MAXN], n;
bool rgt[MAXN];
ll ans;

int seg[MAXN * 4], tag[MAXN * 4];

int getN (int o) {
    return tag[o] + seg[o];
}

void pull (int o) {
    seg[o] = min(getN(o<<1), getN(o<<1|1));
}

void build (int o, int l, int r) {
    if (r == l + 1) {
        seg[o] = s[l];
    } else {
        int m = (l + r) >> 1;
        build(o<<1, l, m);
        build(o<<1|1, m, r);
        pull(o);
    }
}

void add (int qL, int qR, int val, int o = 1, int nL = 0, int nR = n) {
    if (qL < nR && qR > nL && qL < qR) {
        if (qL <= nL && nR <= qR) {
            tag[o] += val;
        } else {
            int nM = (nL + nR) >> 1;
            add(qL, qR, val, o<<1, nL, nM);
            add(qL, qR, val, o<<1|1, nM, nR);
            pull(o);
        }
    }
}

int qry () {
    return getN(1);
}

int qid[MAXN];

vector<pii> qmark;
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();

    cin >> pat;
    n = SZ(pat);
    
    if (!valid()) {
        cout << -1 << endl;
        return 0;
    }

    REP (i, cnt) {
        cin >> a[i] >> b[i];
    }
    if (pat.back() == '?') {
        ans += b[--cnt];
        pat.back() = ')';
    }

    int op = 0;
    REP (i, n) {
        auto c = pat[i];
        if (c == '(') {
            op++;
        } else if (c == ')') {
            op--;
        } else {
            int id = SZ(qmark);
            qid[i] = id;
            qmark.eb(b[id] - a[id], i);
        }
        s[i] = (op + SZ(qmark)) / 2;
    }
    pary(s, s+cnt);

    sort(ALL(qmark));

    build(1, 0, n);

    for (auto m : qmark) {
        add(m.Y, n, -1);
        debug(m.Y);
        debug(qry());

        if (qry() < 0) {
            add(m.Y, n, 1);
            ans += a[qid[m.Y]];
            pat[m.Y] = '(';
        } else {
            ans += b[qid[m.Y]];
            pat[m.Y] = ')';
        }
    }

    cout << ans << endl;
    cout << pat << endl;

    return 0;
}
