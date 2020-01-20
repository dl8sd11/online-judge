#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, f[MAXN], w[MAXN];
vector<int> lst[MAXN];

ll ans;

ll seg[MAXN*4], tag[MAXN*4];

ll get (int o) {
    return seg[o] + tag[o];
}

void push (int o) {
    if (tag[o]) {
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        seg[o] += tag[o];
        tag[o] = 0;
    }
}

void pull (int o) {
    seg[o] = max(get(o<<1), get(o<<1|1));
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

ll qry (int qL, int qR, int o, int nL, int nR) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return -INF;
    } else if (qL <= nL && nR <= qR) {
        return get(o);
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        return max(qry(qL, qR, o<<1, nL, nM), \
                qry(qL, qR, o<<1|1, nM, nR));
    }
}

/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> m;
    REP (i, n) {
        cin >> f[i];
    }
    REP1 (i, m) {
        cin >> w[i];
        lst[i].emplace_back(n);
    }

    for (int i=n-1;i>=0;i--) {
        lst[f[i]].emplace_back(i);
    }

    REP1 (i, m) {
        if (lst[i].size() > 1) {
            add(lst[i].back(),lst[i][SZ(lst[i])-2], w[i], 1, 0, n);
        }
    }

    REP (i, n) {
        ans = max(ans, qry(i, n, 1, 0, n));
        int j = f[i];
        if (lst[j].size() >= 2) {
            add(lst[j].back(),lst[j][SZ(lst[j])-2], -w[j], 1, 0, n);
            lst[j].pop_back();
        }
        if (lst[j].size() >= 2) {
            add(lst[j].back(),lst[j][SZ(lst[j])-2], w[j], 1, 0, n);
        }
    }

    cout << ans << endl;
}
