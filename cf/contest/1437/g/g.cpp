#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double, double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) static_cast<int>(i.size())
#define FOR(i, j, k, in) for (int i=j; i < (k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j; i >= (k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i, j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(), _a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
template<typename T, typename S>
istream &operator >> (istream &is, pair<T, S> &p) {
    return is >> p.X >> p.Y;
}
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do {\
    fprintf(stderr, "%s - %d (%s) = ", __PRETTY_FUNCTION__, __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T> void _do(T &&_x) {cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x, S &&..._t) {cerr <<_x <<" ,"; _do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s, const pair<_a, _b> &_p) {return _s << "(" << _p.X << "," << _p.Y << ")";}
template<typename It> ostream& _OUTC(ostream &_s, It _ita, It _itb)
{
    _s << "{";
    for (It _it=_ita; _it != _itb; _it++) {
        _s <<(_it == _ita?"":",")<< *_it;
    }
    _s << "}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s, const vector<_a> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _a, size_t _b> ostream &operator << (ostream &_s, const array<_a,_b> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const deque<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s, const map<_a,_b> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;

const int K = 26,MAXN = 300005;


struct edge{
  int u,v,w,n;
}e[MAXN*2];

int dep[MAXN],sz[MAXN],fat[MAXN],son[MAXN],top[MAXN];
int in[MAXN],cnt,idx,head[MAXN];
int seg[MAXN*2];


int ssz;
void chg (int x, int v) {
    for (seg[x+=ssz]=v;x>1; x>>=1) {
        seg[x>>1] = max(seg[x], seg[x^1]);
    }
}

int qry (int l, int r) {
    int ret = -1;
    for (l+=ssz, r+=ssz; l<r; l>>=1, r>>=1) {
        if (l&1) ret = max(ret, seg[l++]);
        if (r&1) ret = max(ret, seg[--r]);
    }
    return ret;
}

void add_edge(int u,int v,int w){
  e[cnt].u = u;
  e[cnt].v = v;
  e[cnt].w = w;
  e[cnt].n = head[u];
  head[u] = cnt++;
}

void dfs1 (int nd,int par) {
  dep[nd] = dep[par] + 1;
  sz[nd] = 1;
  fat[nd] = par;
  son[nd] = 0;
  for (int i=head[nd];i!=-1;i=e[i].n) {
    if (e[i].v==par) continue;
    dfs1(e[i].v,nd);
    sz[nd] += sz[e[i].v];
    if(sz[e[i].v] > sz[son[nd]]) son[nd] = e[i].v;
  }
}

void dfs2 (int nd,int tp) {
  in[nd] = idx++;
  top[nd] = tp;
  if (son[nd]) dfs2(son[nd],tp);
  for (int i=head[nd];i!=-1;i=e[i].n) {
    if (e[i].v==fat[nd] || e[i].v==son[nd]) continue;
    dfs2(e[i].v,e[i].v);
  }
}

struct Trie {
    int nxt[K], go[K], pid, pch, leaf = -1, link = -1, lst = -1;
    Trie (int _pid=0, int _pch=0) {
        memset(nxt, -1, sizeof(nxt));
        memset(go, -1, sizeof(go));
        pid = _pid;
        pch = _pch;
    }
};
vector<Trie> trie(1);
vector<int> occ[MAXN];

int addString (string &str, int id) {
    int nd = 0;
    for (auto c : str) {
        int cid = c - 'a';
        if (trie[nd].nxt[cid] == -1) {
            trie[nd].nxt[cid] = SZ(trie);
            trie.emplace_back(nd, cid);
        }
        nd = trie[nd].nxt[cid];
    }
    trie[nd].leaf = id;
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

int getLast (int nd) {
    if (trie[nd].lst == -1) {
        if (trie[getLink(nd)].leaf == -1) {
            trie[nd].lst = nd == 0 ? 0 : getLast(getLink(nd));
        } else {
            trie[nd].lst = getLink(nd);
        }
    }
    return trie[nd].lst;
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

int hld_qry (int nd) {
    int ans = -1;
    while (nd >= 0) {
        ans = max(ans, qry(in[top[nd]], in[nd]+1));
        nd = fat[top[nd]];
    }
    return ans;
}

int query (string &str) {
    int nd = 0;
    int ans = -1;
    for (auto c : str) {
        int cid = c - 'a';
        nd = go(nd, cid);
        ans = max(ans, hld_qry(nd));
    }
    return ans;
}

signed main () {
    TIME(main);
    IOS();

    int n, m;
    cin >> n >> m;
    vector<int> trie_id(n);
    for (int i=0; i<n; i++) {
        string name;
        cin >> name;
        trie_id[i] = addString(name, i);
    }
    memset(head, -1, sizeof(head));
    memset(seg, -1, sizeof(seg));
    ssz = SZ(trie);

    for (int i=1; i<SZ(trie); i++) {
        add_edge(getLink(i), i, 0);
        debug(trie[i].link, i);
    }
    dfs1(0, 0);
    dfs2(0, 0);
    fat[0] = -1;
    vector<multiset<int> > mx(ssz);
    for (int i=0; i<n; i++) {
        mx[trie_id[i]].insert(0);
    }
    for (int i=0; i<n; i++) {
        chg(in[trie_id[i]], 0);
    }

    vector<int> org(n, 0);
    for (int i=0; i<m; i++) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int id, v;
            cin >> id >> v;
            id--;

            int tid = trie_id[id];
            mx[tid].erase(mx[tid].find(org[id]));
            mx[tid].insert(v);
            org[id] = v;
            debug(trie_id[id]);
            chg(in[trie_id[id]], *prev(mx[tid].end()));
        } else {
            string name;
            cin >> name;
            cout << query(name) << endl;
        }
    }



    return 0;
}
