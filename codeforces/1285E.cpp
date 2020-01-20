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


const int MAXN = 200005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

template<typename T>
class ValueToRank {
private:
    vector<T> value;
public:
    void clear () {
        value.clear();
    }

    void addValue (T val) {
        value.emplace_back(val);
    }

    int getRank (T val) {
        return int(lower_bound(value.begin(),value.end(),val)-value.begin());
    }

    int build() {
        sort(value.begin(),value.end());
        int len = unique(value.begin(),value.end())-value.begin();
        value.resize(len);
        return len;
    }
};


int t, n, c;
vector<int> l, r;

struct Query {
    int id, add;
};
vector<Query> query[MAXN*2];

void build () {
    REP (i, n) {
        query[l[i]].push_back({i, 1});
        query[r[i]].push_back({i, -1});
    }
}

int res[MAXN];
int solve () {
    set<int> open;
    memset(res, 0, sizeof(res));

    int lst = -1, sum = 0;
    REP (pos, c) {
        vector<Query> lseg, rseg;
        for (auto q : query[pos]) {
            if (q.add == 1) {
                lseg.emplace_back(q);
            } else {
                rseg.emplace_back(q);
            }
        }

        if (lseg.size() >= 1 && open.size() == 1) {
            res[*open.begin()]++;
        }

        for (auto seg : lseg) {
            if (lst == -1) {
                lst = pos;
                sum++;
                if (lseg.size() == 1) {
                    res[seg.id]--;
                }
            }
            open.insert(seg.id);
        }
        for (auto seg : rseg) {
            open.erase(seg.id);
            if (open.empty()) {
                lst = -1;
            }
        }

        query[pos].clear();
    }

    pary(res, res+n);
    REP (i, MAXN) {
        res[i] += sum;
    }
    debug(sum);

    return *max_element(res,res+n);
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    ValueToRank<int> v2r;

    cin >> t;
    while (t--) {
        cin >> n;

        l.resize(n), r.resize(n);
        v2r.clear();
        REP (i, n) {
            cin >> l[i] >> r[i];
            v2r.addValue(l[i]);
            v2r.addValue(r[i]);
        }
        c = v2r.build();
        REP (i, n) {
            l[i] = v2r.getRank(l[i]);
            r[i] = v2r.getRank(r[i]);
        }

        build();
        cout << solve() << endl;
    }

}

