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
template<typename T> ostream &operator << (ostream &os,pair<T,T> &v){return os<<"{"<<v.first<<","<<v.second<<"}";}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif


const int MAXN = 1000006;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, k;
int a[MAXN];
vector<int> pos[MAXN];

pair<ll,int> ans;

const int sz = 2;
typedef array<ll,sz> asz;

ostream& operator << (ostream &os, const asz &a) {
    os << "{";
    REP (i, sz) {
        os << a[i] << ",}" [i==sz-1];
    }
    return os;
}

const ll mod[sz] = {1000000007, 1000000009};
asz cb = {20020607, 279936};
asz cc = {1, 1};

array<ll,sz> dt;
asz operator + (const asz &a1, const asz &a2) {
    asz ret;
    REP (i, sz) {
        ret[i] = a1[i] + a2[i];
        if (ret[i] >= mod[i]) {
            ret[i] -= mod[i];
        }
    }
    return ret;
}

void operator += (asz &a1, const asz &a2) {
    REP (i, sz) {
        a1[i] = a1[i] + a2[i];
        if (a1[i] >= mod[i]) {
            a1[i] -= mod[i];
        }
    }
}

asz neg (const asz &a) {
    asz ret;
    REP (i, sz) {
        ret[i] = mod[i] - a[i];
    }
    return ret;
}

template<typename T>
class BIT {
public:
    T bit[MAXN];

    void add (int x, T val) {
        for (x++;x<MAXN;x+=-x&x) {
            bit[x] += val;
        }
    }

    void qry (int x, T &ret) {
        for (x++;x>0;x-=-x&x) {
            ret += bit[x];
        }
    }
};

BIT<int> cnt;
BIT<asz> hsh;

void iterc () {
    REP (i, sz) {
        cc[i] = cc[i] * cb[i] % mod[i];
    }
}


void addRng (asz val, int l, int r) { // [l,r]
    hsh.add(l, val);
    hsh.add(r+1, neg(val));
    cnt.add(l, 1);
    cnt.add(r+1, -1);
}

vector<pair<asz,int> > srt;

int dis (const vector<int> &id) {
    if (SZ(id) == 1) {
        return n;
    }
    vector<int> nw = id;
    for (auto v : id) {
        nw.emplace_back(v + n);
    }

    int idx = 1;
    int mn = n;
    for (int i=0;i<SZ(id);i++) {
        while (nw[idx]-nw[i]<=n/2) {
            idx++;
        }
        debug(nw[i], nw[idx-1]);
        int d = nw[idx-1]-nw[i];
        mn = min(mn, (n-d)-d);
    }
    debug(nw, mn);

    return mn;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    REP (i, n) {
        cin >> a[i];
        pos[a[i]].emplace_back(i);
    }

    asz ze = {0, 0};
    REP (i, MAXN) {
        hsh.bit[i] = ze;
        cnt.bit[i] = 0;
    }

    REP1 (i, k) {
        for (int j=1;j<SZ(pos[i]);j++) {
            iterc();
            addRng(cc, pos[i][j-1]+1, pos[i][j]);
        }
        iterc();
        addRng(cc, 0, pos[i].front());
        addRng(cc, pos[i].back()+1, n-1);
    }

    REP (i, n) {
        int x = 0;
        cnt.qry(i, x);
        debug(x);
        if (x == k) {
            asz ret = {0, 0};
            hsh.qry(i, ret);
            srt.emplace_back(ret, i);
            debug(ret);
        }
    }
    sort(srt.begin(),srt.end());

    debug("test");

    ans.second = n;
    vector<int> id = {srt[0].second};
    REP1 (i, n) {
        if (i==n || srt[i].first != srt[i-1].first) {
            ans.first += 1LL * SZ(id) * (SZ(id)-1) / 2;
            ans.second = min(ans.second, dis(id));

            debug(id);
            id.clear();
        }
        if (i != n) {
            id.emplace_back(srt[i].second);
        }
    }


    cout << ans.first << " " << ans.second << endl;
}
