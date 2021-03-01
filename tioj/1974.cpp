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

const int MAXN = 200005;
const ll MOD = 1000000007;

int n;

struct Rect {
    int r0, c0, r1, c1, w;
};
Rect rect[MAXN];

void dc (int &x, vector<int> &srt) {
    x = lower_bound(ALL(srt), x)-srt.begin();
}

vector<int> add[MAXN], sub[MAXN];

int line[MAXN];

struct RMQ {
    int mx[MAXN*4], tag[MAXN*4];

    int get (int o) {
        return mx[o] + tag[o];
    }

    void pull (int o) {
        mx[o] = max(get(o<<1), get(o<<1|1));
    }

    void push (int o) {
        if (tag[o]) {
            mx[o] += tag[o];
            tag[o<<1] += tag[o];
            tag[o<<1|1] += tag[o];
            tag[o] = 0;
        }
    }

    void build (int o, int nL, int nR) {
        if (nL == nR - 1) {
            mx[o] = line[nL];
            tag[o] = 0;
        } else {
            int nM = (nL + nR) >> 1;
            build(o<<1, nL, nM);
            build(o<<1|1, nM, nR);
            pull(o);
        }
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

    int qry () {
        return get(1);
    }
} rmq;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    vector<int> x, y;
    REP (i, n) {
        cin >> rect[i].r0 >> rect[i].c0 >> rect[i].r1 >> rect[i].c1 >> rect[i].w;
        x.eb(rect[i].r0);
        x.eb(rect[i].r1);
        y.eb(rect[i].c0);
        y.eb(rect[i].c1);
    }

    sort(ALL(x));
    sort(ALL(y));
    x.resize(unique(ALL(x))-x.begin());
    y.resize(unique(ALL(y))-y.begin());

    REP (i, n) {
        dc(rect[i].r0, x);
        dc(rect[i].r1, x);
        dc(rect[i].c0, y);
        dc(rect[i].c1, y);
    }

    REP (i, n) {
        debug(rect[i].c0, rect[i].c1);
        line[rect[i].c0]+=rect[i].w;
        line[rect[i].c1+1]-=rect[i].w;
    }

    int sum = 0;
    REP (i, SZ(y)) {
        sum += line[i];
        line[i] = sum;
    }
    pary(line, line+SZ(y));

    REP (i, n) {
        add[rect[i].r0].eb(i);
        sub[rect[i].r1].eb(i);
    }

    int sz = SZ(y);
    rmq.build(1, 0, sz);

    int ans = 0, cur = 0;
    REP (i, SZ(x)) {
        for (auto v : add[i]) {
            rmq.add(rect[v].c0, rect[v].c1+1, -rect[v].w, 1, 0, sz);
            cur += rect[v].w;
        }
        ans = max(ans, rmq.qry()+cur);
        for (auto v : sub[i]) {
            rmq.add(rect[v].c0, rect[v].c1+1, rect[v].w, 1, 0, sz);
            cur -= rect[v].w;
        }
    }

    cout << ans << endl;
}
