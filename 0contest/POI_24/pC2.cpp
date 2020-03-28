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

const int MAXN = 1000006;
const ll MOD = 1000000007;

int n, z, a[MAXN];

pair<int,int> seg[MAXN*4];
int tag[MAXN*4];

pair<int,int> get (int o) {
    return {tag[o]+seg[o].X, seg[o].Y};
}

void push (int o) {
    if (tag[o]) {
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        seg[o].X += tag[o];

        tag[o] = 0;
    }
}

void pull (int o) {
    pii lres = get(o<<1), rres = get(o<<1|1);
    if (lres.X > rres.X) {
        swap(lres, rres);
    }
    if (lres.X == rres.X) {
        seg[o] = {lres.X, lres.Y + rres.Y};
    } else {
        seg[o] = lres;
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

void build (int o, int nL, int nR) {
    if (nL == nR - 1) {
        seg[o] = {MOD, 1};
    } else {
        int nM = (nL + nR) >> 1;
        build(o<<1, nL, nM);
        build(o<<1|1, nM, nR);
        pull(o);
    }
}

void pattern (int x, int dl) {
    if (x >= 1 && x <= n) {
        pair<int,int> rng = {a[x], a[x+1]};
        if (rng.X > rng.Y) {
            swap(rng.X, rng.Y);
        }

        add(rng.X, rng.Y, dl, 1, 1, n+1);
    }
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> z;

    REP1 (i, n) {
        cin >> a[i];
    }
    a[n+1] = MOD;

    build(1, 1, n+1);

    REP1 (i, n) {
        pattern(i, 1);
    }

    cout << get(1).Y << endl;
    while (--z) {
        int u, v;
        cin >> u >> v;
        pattern(u-1, -1);
        pattern(u,-1);
        pattern(v-1, -1);
        pattern(v, -1);

        swap(a[u], a[v]);

        pattern(u-1, 1);
        pattern(u,1);
        pattern(v-1, 1);
        pattern(v, 1);

        cout << get(1).Y << endl;
    }

}
