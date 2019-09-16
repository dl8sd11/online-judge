#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<int, ll> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
// const ll MAXN = 

struct Trie {
    Trie *ch[2];
    int mn;
    Trie () {
        ch[0] = ch[1] = nullptr;
        mn = iNF;
    }

    void pull () {
        if (ch[0]) {
            mn = min(mn, ch[0]->mn);
        }
        if (ch[1]) {
            mn = min(mn, ch[1]->mn);
        }
    }
};
Trie *trie[100005];
void add (Trie *nd, int num, int idx) {
    bool cur = (num>>idx)&1;
    if (!nd->ch[cur]) {
        nd->ch[cur] = new Trie();
    }
    if (idx == 0) {
        nd->ch[cur]->mn = num;
        nd->pull();
    } else {
        add(nd->ch[cur], num, idx-1);
        nd->pull();
    }
}

int qry (Trie *nd, int num, int bd, int idx) {
    bool cur = (num>>idx)&1;
    if (nd->ch[!cur] && nd->ch[!cur]->mn <= bd) {
        return idx ? qry(nd->ch[!cur], num, bd, idx-1) : nd->ch[!cur]->mn;
    } else if (nd->ch[cur] && nd->ch[cur]->mn <= bd) {
        return idx ? qry(nd->ch[cur], num, bd, idx-1) : nd->ch[cur]->mn;
    } else {
        debug(num, bd, idx);
        return -1;
    }
}
int q;
bool exi[100005];
vector<int> divi[100005];
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    for (int i=1; i<=100000; i++) {
        trie[i] = new Trie();
        for (int j=i; j<=100000; j+=i) {
            divi[j].eb(i);
        }
    }

    cin >> q;
    while (q--) {
        int cmd, u, x, k, s;
        cin >> cmd;
        if (cmd == 1) {
            cin >> u;
            if (!exi[u]) {
                exi[u] = true;
                for (auto d : divi[u]) {
                    add(trie[d], u, 18);
                }
            }
        } else {
            cin >> x >> k >> s;
            if (x % k != 0) {
                cout << -1 << endl;
            } else {
                debug(x, s-x, trie[k]->mn);
                cout << qry(trie[k], x, s-x, 18) << endl;
            }
        }
    }
    return 0;
}
