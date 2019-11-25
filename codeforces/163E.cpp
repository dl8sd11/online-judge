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

int bit[MAXN];

void addBit (int x, int val) {
    for (x++; x<MAXN; x+=-x&x) {
        bit[x] += val;
    }
}

int qryBit (int x) {
    int ret = 0;
    for (x++; x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int in[MAXN], out[MAXN], tme, nid[MAXN];
vector<int> edge[MAXN];
bool isOn[MAXN];

const int K = 26;
struct Trie {
    int go[K], pid, pch, link = -1;
    Trie (int _pid=0, int _pch=0) {
        pid = _pid;
        pch = _pch;
        memset(go, -1, sizeof(go));
    }
};
vector<Trie> trie(1);

int addString (string &s) {
    int nd = 0;
    for (auto c : s) {
        int cid = c - 'a';
        if (trie[nd].go[cid] == -1) {
            trie[nd].go[cid] = SZ(trie);
            trie.emplace_back(nd, cid);
        }
        nd = trie[nd].go[cid];
    }
    return nd;
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
        trie[nd].go[cid] = nd == 0 ? 0 : go(getLink(nd), cid);
    }
    return trie[nd].go[cid];
}

int query (const string &s) {
    int ret = 0;
    int nd = 0;
    for (auto c : s) {
        int cid = c - 'a';
        nd = go(nd, cid);
        ret += qryBit(in[nd]);
    }
    return ret;
}

void setOn (int nd) {
    if (!isOn[nd]) {
        addBit(in[nd], 1);
        addBit(out[nd], -1);
        isOn[nd] ^= 1;
    }
}

void setOff (int nd) {
    if (isOn[nd]) {
        addBit(in[nd], -1);
        addBit(out[nd], 1);
        isOn[nd] ^= 1;
    }
}

void dfs (int nd) {
    in[nd] = tme++;
    for (auto v : edge[nd]) {
        dfs(v);
    }
    out[nd] = tme;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    int q, n;
    cin >> q >> n;
    REP (i, n) {
        string s;
        cin >> s;
        nid[i] = addString(s);
    }
    assert(SZ(trie) < MAXN);

    REP1 (i, SZ(trie)-1) {
        edge[getLink(i)].emplace_back(i);
    }
    dfs(0);

    REP (i, n) {
        setOn(nid[i]);
    }

    while (q--) {
        string cur;
        cin >> cur;
        if (cur[0] == '?') {
            cout << query(cur.substr(1)) << endl;
        } else {
            int id = atoi(cur.substr(1).c_str()) - 1;
            if (cur[0] == '+') {
                setOn(nid[id]);
            } else if (cur[0] == '-'){
                setOff(nid[id]);
            }
        }
    }

}
