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

const int MAXN = 1003;
const ll MOD = 1000000007;
const int K = 52;

struct Trie {
    int nxt[K], go[K];
    int leaf = -1, pid, link = -1, pch;
    bool vis = false;
    Trie (int _pid=-1, int _pch='$') {
        memset(nxt, -1, sizeof(nxt));
        memset(go, -1, sizeof(nxt));
        pid = _pid;
        pch = _pch;
    }
};
vector<Trie> trie;

int lcnt;
bool ans[MAXN];
string t[MAXN];

int getCharID (char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    } else {
        return c - 'a' + 26;
    }
}

void addString (string &s, int id) {
    int nd = 0;
    for (auto c : s) {
        int cid = getCharID(c);
        if (trie[nd].nxt[cid] == -1) {
            trie[nd].nxt[cid] = SZ(trie);
            trie.emplace_back(nd, cid);
        }
        nd = trie[nd].nxt[cid];
    }
    trie[nd].leaf = id;
}

int go (int nd, int cid);

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

int go (int nd, int cid) {
    if (trie[nd].go[cid] == -1) {
        if (trie[nd].nxt[cid] != -1) {
            trie[nd].go[cid] = trie[nd].nxt[cid];
        } else {
            trie[nd].go[cid] = nd == 0 ? 0 : go(getLink(nd), cid);
        }
    }
    return trie[nd].go[cid];
}

void query (string &s) {
    int nd = 0;
    for (auto c : s) {
        debug(c);
        int cid = getCharID(c);
        nd = go(nd, cid);

        int ptr = nd;
        while (ptr != 0 && !trie[ptr].vis) {
            if (trie[ptr].leaf != -1) {
                ans[trie[ptr].leaf] = true;
            }
            trie[ptr].vis = true;
            ptr = getLink(ptr);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    int k, q;
    string s;
    cin >> k;
    while (k--) {
        map<string, int> sid;
        trie.resize(1);
        lcnt = 0;
        cin >> s;
        cin >> q;
        REP (i, q) {
            cin >> t[i];
            if (sid.count(t[i]) == 0) {
                sid[t[i]] = ++lcnt;
                addString(t[i], lcnt);
            }
        }

        memset(ans, 0, sizeof(ans));

        query(s);
        REP (i, q) {
            if (ans[sid[t[i]]]) {
                cout << 'y' << endl;
            } else {
                cout << 'n' << endl;
            }
        }

        trie.clear();
    }

    debug(k);
}
