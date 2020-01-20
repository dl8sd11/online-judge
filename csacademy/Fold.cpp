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
template<typename T> ostream &operator << (ostream &os,deque<T> &v){return _printRng(os,v.begin(), v.end());}
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

int n, q, l, r, hd[MAXN], tl[MAXN], link[MAXN], sz[MAXN];
bool rev = false;

void connect (int u, int v) {
    link[u] ^= u ^ v;
    link[v] ^= u ^ v;
}

void mrg (int f, int t, bool bot) {
    sz[t] += sz[f];
    if (!bot) {
        connect(tl[f], tl[t]);
        tl[t] = hd[f];
    } else {
        connect(hd[f], hd[t]);
        hd[t] = tl[f];
    }
}

void printList(int st, int ed) {
    int lst = st, cur = st;
    while (true) {
        int tmp = cur;
        cout << cur;
        cur = link[cur] ^ lst;
        lst = tmp;

        if (tmp == ed) {
            cout << endl;
            break;
        } else {
            cout << " ";
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> q;
    REP1 (i, n) {
        hd[i] = tl[i] = i;
        sz[i] = 1;
    }
    l = 1, r = n;
    while (q--) {
        int p;
        cin >> p;

        if (rev) {
            p = r - p;
        } else {
            p = l + p-1;
        }
        debug(l, r, p);

        if (p < (r+l)/2) {
            for (int i=l;i<=p;i++) {
                mrg(i,p+(p-i+1), rev);
            }
            if (!rev) {
                rev = true;
            }
            l = p + 1;
        } else {
            for (int i=p+1;i<=r;i++) {
                mrg(i,p-(i-p-1), rev);
            }
            if (rev) {
                rev = false;
            }
            r = p;
        }

        #ifdef tmd
        debug(l, r, p, rev);
        for (int i=l;i<=r;i++) {

            debug(hd[i], tl[i]);
        }

        #endif // tmd
    }

    if (rev) {
        int mx = l;
        for (int i=l;i<=r;i++) {
            if (sz[i] >= sz[mx]) {
                mx = i;
            }
        }

        printList(tl[mx], hd[mx]);
        for (int i=r;i>=l;i--) {
            cout << tl[i] << " \n"[i==l];
        }
        for (int i=r;i>=l;i--) {
            cout << hd[i] << " \n"[i==l];
        }
    } else {
        int mx = r;
        for (int i=r;i>=l;i--) {
            if (sz[i] >= sz[mx]) {
                mx = i;
            }
        }

        printList(hd[mx], tl[mx]);
        for (int i=l;i<=r;i++) {
            cout << hd[i] << " \n"[i==r];
        }
        for (int i=l;i<=r;i++) {
            cout << tl[i] << " \n"[i==r];
        }
    }
}
/*
8 4
0 6 0 1

*/
