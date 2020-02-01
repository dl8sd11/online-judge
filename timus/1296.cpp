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

const int MAXN = 100005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

typedef int uchar;
int n;

struct Trie {
    map<uchar,int> nxt;
    int pid;
    uchar pch;
    int link;
    int leaf;
    Trie (int _pid=0,uchar _pch='\0') {
        pid = _pid;
        pch = _pch;
        link = -1;
        leaf = -1;
    }
};
vector<Trie> trie(1);

void addString () {
    int nd = 0;
    int cnt = 0;
    while (true) {
        uchar c = getchar();
        if (c == '\n') {
            break;
        }
        cnt++;
        if (trie[nd].nxt.count(c) == 0) {
            trie.emplace_back(nd, c);
            trie[nd].nxt[c] = SZ(trie) - 1;
        }
        nd = trie[nd].nxt[c];
    }
    trie[nd].leaf = cnt;
}

int go (int nd, uchar c);

int getLink (int nd) {
    if (trie[nd].link == -1) {
        if (nd == 0 || trie[nd].pid == 0) {
            trie[nd].link = 0;
        } else {
            trie[nd].link = go(getLink(trie[nd].pid), trie[nd].pch);
        }
    }
    return trie[nd].link;
}

int go (int nd, uchar c) {
    if (trie[nd].nxt.count(c) == 0) {
        if (nd == 0) {
            trie[nd].nxt[c] = 0;
        } else {
            trie[nd].nxt[c] = go(getLink(nd), c);
        }
    }
    return trie[nd].nxt[c];
}

int getLeaf (int nd) {
    if (trie[nd].leaf == -1) {
        if (nd == 0) {
            trie[nd].leaf = 0;
        } else {
            trie[nd].leaf = getLeaf(getLink(nd));
        }
    }
    return trie[nd].leaf;
}

int solve () {
    int nd = 0;
    int ret = MOD;
    int i = 0;
    while (true) {
        uchar c = getchar();
        if (c == '\n') {
            break;
        }
        nd = go(nd, c);
        int leaf = getLeaf(nd);
        if (leaf > 0) {
            ret = min(ret, i-leaf+1);
        }
        i++;
    }
    return ret == MOD ? -1 : ret + 1;
}

/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n;
    cin.ignore();
    REP (i, n) {
        addString();
    }

    pair<int,int> ans = {-1, -1};
    cin >> n;
    cin.ignore();
    REP1 (i, n) {
        if (ans.first == -1) {
            int fnd = solve();
            if (fnd != -1) {
                ans = {i, fnd};
            }
        } else {
            solve();
        }
    }

    if (ans.first == -1) {
        cout << "Passed" << endl;
    } else {
        cout << ans.first << " " << ans.second << endl;
    }
}
