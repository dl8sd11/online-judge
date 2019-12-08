#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops,no-stack-protector")

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=(k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#define HI
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &_x){cerr<<_x<<endl;}
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
const ll MAXN = 1000006;

int n;
char c[MAXN];




typedef pair<int,int> pii;
struct SegmentTree {
    pii dt[MAXN*4];
    int tag[MAXN*4], sum;

    SegmentTree () {
        MEM(tag, 0);
    }

    void push (int o) { // not call it by leaf
        if (tag[o]) {
            tag[o<<1] += tag[o];
            tag[o<<1|1] += tag[o];
            dt[o].first += tag[o];
            dt[o].second += tag[o];
            tag[o] = 0;
        }
    }

    pii mrg(const pii &p1, const pii &p2) {
        return {min(p1.first,p2.first), max(p1.second, p2.second)};
    }

    pii get (int o) {
        return {dt[o].first+tag[o], dt[o].second+tag[o]};
    }

    void pull (int o) {
        dt[o] = mrg(get(o<<1), get(o<<1|1));
    }

    void add (int qL, int qR, int val, int o, int nL, int nR) {
        if (qL >= nR || qR <= nL || qL >= qR) {
            return;
        } else if (qL <= nL && nR <= qR) {
            tag[o] += val;
        } else {
            push(o);
            int nM = (nL + nR) >> 1;
            add(qL, qR, val, o<<1, nL, nM);
            add(qL, qR, val, o<<1|1, nM, nR);
            pull(o);
        }
    }

    pii getTop () {
        push(1);
        return dt[1];
    }
} pre, suf;

int getC (int idx, int rev) {
    if (c[idx] == '(') {
        return 1 * rev;
    } else if (c[idx] == ')') {
        return -1 * rev;
    } else {
        return 0;
    }
}

int minColor () {
    pii pRet = pre.getTop();
    pii sRet = suf.getTop();

    bool tail0 = pre.sum == 0 && suf.sum == 0;
    if (pRet.first < 0 || pRet.first < 0 || !tail0) {
        return -1;
    } else {
        return max(pRet.second, sRet.second);
    }
}

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    cin >> n;
    debug(n);

    int pos = 0;
    REP (u, n) {
        char cmd;
        cin >> cmd;
        if (cmd == 'R') {
            pos++;
        } else if (cmd == 'L') {
            pos = max(0, pos - 1);
        } else {
            int porg = getC(pos,1);
            int sorg = getC(pos,-1);

            c[pos] = cmd;

            pre.add(pos, n, getC(pos,1)-porg, 1, 0, n);
            pre.sum += getC(pos,1)-porg;
            suf.add(0, pos+1, getC(pos,-1)-sorg, 1, 0, n);
            suf.sum += getC(pos,-1)-sorg;
        }
        cout << minColor() << " \n"[u==n-1];
    }


    return 0;
}
