#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 200005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

struct Work {
    int l, r, id;
    ll p;
    bool operator < (const Work &oth) const {
        return l < oth.l;
    }
} work[MAXN];

int n;
ll k, seg[MAXN*4], tag[MAXN*4], pos[MAXN*4];

void push (int o) {
    if (tag[o]) {
        seg[o] += tag[o];
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        tag[o] = 0;
    }
}

ll get (int o) {
    return seg[o] + tag[o];
}

void pull (int o) {
    if (get(o<<1) > get(o<<1|1)) {
        seg[o] = get(o<<1);
        pos[o] = pos[o<<1];
    } else {
        seg[o] = get(o<<1|1);
        pos[o] = pos[o<<1|1];
    }
}

void build (int o, int L, int R) {
    if (L == R - 1) {
        pos[o] = L;
    } else {
        int M = (L + R) >> 1;
        build(o<<1, L, M);
        build(o<<1|1, M, R);
        pull(o);
    }
}

void add (int qL, int qR, ll val, int o,int nL, int nR) {
    if (qL >= qR || qL >= nR || qR <= nL) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o] += val;
    } else {
        int nM = (nL + nR) >> 1;
        push(o);
        add(qL, qR, val, o<<1, nL, nM);
        add(qL, qR, val, o<<1|1, nM, nR);
        pull(o);
    }
}

pair<ll,int> qry (int qL, int qR, int o, int nL, int nR) {
    if (qL >= qR || qL >= nR || qR <= nL) {
        return {-INF, 0};
    } else if (qL <= nL && nR <= qR) {
        return {get(o), pos[o]};
    } else {
        int nM = (nL + nR) >> 1;
        push(o);
        return max(qry(qL, qR, o<<1, nL, nM), qry(qL, qR, o<<1|1, nM, nR));
    }
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    build(1, 0, MAXN);
    REP1 (i, MAXN-1) {
        add(i, i+1, -k*i, 1, 0, MAXN);
    }
    REP (i, n) {
        cin >> work[i].l >> work[i].r >> work[i].p;
        work[i].id = i;
        add(work[i].r, MAXN, work[i].p, 1, 0, MAXN);
    }
    sort(work, work+n);

    int idx = 0;

    ll ans = 0;
    int ansL, ansR;
    REP1 (i, MAXN) {
        while (idx < n && work[idx].l < i) {
            add(work[idx].r, MAXN, -work[idx].p, 1, 0, MAXN);
            idx++;
        }
        pair<ll,int> res = qry(i, MAXN, 1, 0, MAXN);

        if (res.first > ans) {
            ans = res.first;
            ansL = i;
            ansR = res.second;
        }

        add(i, MAXN, k, 1, 0, MAXN);
    }

    if (ans == 0) {
        cout << 0 << endl;
    } else {
        vector<int> chosen;
        REP (i, n) {
            if (ansL <= work[i].l  && work[i].r <= ansR) {
                chosen.emplace_back(work[i].id+1);
            }
        }
        cout << ans << " " << ansL << " " << ansR << " " << SZ(chosen) << endl;
        REP (i, SZ(chosen)) {
            cout << chosen[i] << " \n"[i==SZ(chosen)-1];
        }
    }
}
