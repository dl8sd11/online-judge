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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXP = 20;
const int MAXN = (1<<MAXP) + 3;
int q;
int bit[MAXN];

void add (int x, int val) {
    for (;x<MAXN;x+=-x&x) {
        bit[x] += val;
    }
}

inline char readchar()
{
    static const size_t bufsize = 65536;
    static char buf[bufsize];
    static char *p = buf, *end = buf;
    if (p == end) end = buf + fread_unlocked(buf, 1, bufsize, stdin), p = buf;
    return *p++;
}

template <class T> void input(T& a)
{
    static char p;
    while ((p = readchar()) < '0') ;
    a = p ^ '0';
    while ((p = readchar()) >= '0') a *= 10, a += p ^ '0';
}

int lbd (int sz) {
    int sum = 0, pos = 0;
    for (int i=MAXP-1;i>=0;i--) {
        if (sum+bit[pos+(1<<i)] < sz) {
            pos += 1<<i;
            sum += bit[pos];
        }
    }
    return pos + 1;
}
/*********************GoodLuck***********************/
int main () {
#ifdef tmd
    cin >> q;
#else
    input(q);
#endif
    int cnt = 0;
    while (q--) {
        int cmd, d;
#ifdef tmd
        cin >> cmd;
#else
        input(cmd);
#endif // tmd
        debug(cmd);
        if (cmd == 1) {
#ifdef tmd
            cin >> d;
#else
            input(d);
#endif
            d++;
            cnt++;
            add(d, 1);
        } else {
            printf("%d\n",lbd(cnt/2+1)-1);
        }
    }
}
