#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
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
template<typename T> ostream &operator << (ostream &os,const array<T,2> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXC = 1<<16;
const int MAXN = 1<<18;
const ll MOD = 1000000007;

int id[MAXC][17], dis[MAXN];
bool vis[MAXN];
int cnt, n;

array<int,2> w[1003];
array<int,2> state[MAXN];

void build_id () {
    state[cnt] = {0, 0};
    id[0][0] = id[0][0] = cnt++;

    REP1 (d, 16) {
        REP (msk, (1<<d)) {
            state[cnt] = {msk, d};
            id[msk][d] = cnt++;
        }
    }
}

typedef array<int,2> ai2;

inline int sub (const ai2 &bg, const ai2 &sm) {
    if ((bg[0] & ((1<<sm[1]) - 1)) == sm[0]) {
       return id[bg[0]>>sm[1]][bg[1]-sm[1]];
    } else {
        return -1;
    }
}
int solve () {
    memset(dis, 0x3f, sizeof(dis));

    priority_queue<ai2,vector<ai2>,greater<ai2> > pq;
    REP (i, n) {
        REP (j, i) {
            int rid = w[j][1] > w[i][1] ? sub(w[j], w[i]) : sub(w[i], w[j]);
            if (rid != -1) {
                debug(state[rid], w[i], w[j]);
                dis[rid] = max(w[j][1], w[i][1]);
                pq.push({dis[rid], rid});
            }
        }

    }

    while (pq.size()) {
        int cur = pq.top()[1];
        pq.pop();

        if (vis[cur]) {
            continue;
        }
        vis[cur] = true;

//        if (cur == 0) {
//            return dis[cur];
//        }

        REP (i, n) {
            int nw = state[cur][1] > w[i][1] ? sub(state[cur], w[i]) : sub(w[i], state[cur]);
            if (nw != -1) {
                int nd = state[cur][1] > w[i][1] ? dis[cur] : dis[cur]+state[nw][1];

                if (dis[nw] > nd) {
                    dis[nw] = nd;
                    pq.push({dis[nw], nw});
                }
            }
        }
    }

//    #ifdef tmd
//
//    int st, len;
//    while (cin >> st >> len) {
//        debug(dis[id[st][len]]);
//    }
//
//    #endif // tmd
    return dis[0] == 0x3f3f3f3f ? 0 : dis[0];

}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        string str;
        cin >> str;

        int msk = 0;
        REP (j, SZ(str)) {
            msk += str[j]-'0' << j;
        }
        w[i][0] = msk;
        w[i][1] = SZ(str);
    }

    build_id();
    debug(cnt);
    cout << solve() << endl;
}
