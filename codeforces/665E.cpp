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

const int MAXN = 1000006;
const ll MOD = 1000000007;

int n, k, xo[MAXN];

struct Trie {
    Trie *ch[2];
    int cnt, sum;
    Trie () {
        ch[0] = ch[1] = nullptr;
        cnt = sum = 0;
    }
} *root;

void add (int x) {
    Trie *cur = root;
    root->sum++;
    for (int i=30; i>=0; i--) {
        if (!cur->ch[1&(x>>i)]) {
            cur->ch[1&(x>>i)] = new Trie();
        }
        cur = cur->ch[1&(x>>i)];
        cur->sum++;
    }
}

int get (Trie *nd) {
    return nd ? nd->sum : 0;
}

int qry (int x) {
   Trie *cur = root;
   int sum = 0;
   int ret = 0;
   for (int i=30; i>=0; i--) {
        bool c = (x>>i) & 1;
        if ((sum^(1<<i)) >= k) {
            ret += get(cur->ch[c^1]);
            if (!cur->ch[c]) {
                break;
            }
            cur = cur->ch[c];
        } else {
            sum += 1<<i;
            if (!cur->ch[c^1]) {
                break;
            }
            cur = cur->ch[c^1];
        }
   }
   debug(ret);
   return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    root = new Trie();

    add(0);
    ll ans = 0;
    REP1 (i, n) {
        int a;
        cin >> a;
        xo[i] = xo[i-1] ^ a;
        int res = qry(xo[i]);
        ans += res;
        debug(xo[i]);
        debug(res);
        add(xo[i]);
    }

    cout << ans << endl;

    return 0;
}
