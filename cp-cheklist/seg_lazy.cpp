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

const int MAXN = 500005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
ll a[MAXN], tag[MAXN*4], seg[MAXN*4];

ll get (int o) {
    return seg[o] + tag[o];
}

void pull (int o) {
    seg[o] = min(get(o<<1), get(o<<1|1));
}

void push (int o) {
    if (tag[o]) {
        seg[o] += tag[o];
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        tag[o] = 0;
    }
}

void build (int o=1, int l=0, int r=n) {
    if (l == r - 1) {
        seg[o] = a[l];
    } else {
        int m = (l + r) >> 1;
        build(o<<1, l, m);
        build(o<<1|1, m, r);
        pull(o);
    }
}

void Add (int qL, int qR, int val, int o=1, int nL=0, int nR=n) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o] += val;
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        Add(qL, qR, val, o<<1, nL, nM);
        Add(qL, qR, val, o<<1|1, nM, nR);
        pull(o);
    }
}

ll Qry (int qL, int qR, int o=1, int nL=0, int nR=n) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return INF;
    } else if (qL <= nL && nR <= qR) {
        return get(o);
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        return min(Qry(qL, qR, o<<1, nL, nM), Qry(qL, qR, o<<1|1, nM, nR));
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    cin.ignore();
    REP (i, n) {
        cin >> a[i];
    }
    build(1, 0, n);

    cin.ignore();

    int m, tmp;
    cin >> m;
    cin.ignore();

    while (m--) {
        string str;
        getline(cin, str);
        vector<int> qry;
        stringstream ss(str);
        while (ss >> tmp) {
            qry.emplace_back(tmp);
        }

        debug(qry[0], qry[1]);
        if (qry.size() == 3) {
            if (qry[0] <= qry[1]) {
                Add(qry[0], qry[1]+1, qry[2]);
            } else {
                Add(0, qry[1]+1, qry[2]);
                Add(qry[0], n, qry[2]);
            }
        } else {
            ll mn = INF;
            if (qry[0] <= qry[1]) {
                mn = min(mn, Qry(qry[0], qry[1]+1));
            } else {
                mn = min(mn, Qry(0, qry[1]+1));
                mn = min(mn, Qry(qry[0], n));
            }
            cout << mn << endl;
        }
    }

}
