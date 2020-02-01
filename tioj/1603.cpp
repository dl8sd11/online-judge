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

template<typename T>
class RMQ {

private:
    int djs[MAXN];
    int fnd (int x) {
        return djs[x] == -1 ? x : djs[x] = (fnd(djs[x]));
    }
    vector<pair<int,int> > queryLeftId[MAXN];
public:
    int qsz, dsz;
    vector<pair<int,int> > query;
    vector<T> data, result;
    vector<int> stk;

    void build (bool (*cmp)(T,T)) {
        qsz = query.size();
        dsz = data.size();

        result.resize(qsz);
        for (int i=0;i<int(qsz);i++) {
            auto lr = query[i];
            queryLeftId[lr.second].emplace_back(lr.first, i);
        }
        stk.reserve(qsz / 4);


        memset(djs, -1, sizeof(int)*dsz);
        for (int i=0;i<dsz;i++) {
            while (!stk.empty() && cmp(data[i], data[stk.back()])) {
                djs[stk.back()] = i;
                stk.pop_back();
            }
            stk.emplace_back(i);
            for (pair<int,int> lid : queryLeftId[i]) {
                result[lid.second] = data[fnd(lid.first)];
            }
        }
    }
};

typedef unsigned int ui;

bool gt (ui a, ui b) {
    return a > b;
}

bool ls (ui a, ui b) {
    return a < b;
}

RMQ<ui> mn, mx;
/*********************GoodLuck***********************/
int main () {
    IOS();

    int n, m;
    cin >> n >> m;

    REP (i, n) {
        ui d;
        cin >> d;
        mx.data.emplace_back(d);
        mn.data.emplace_back(d);
    }

    REP (i, m) {
        int l, r;
        cin >> l >> r;
        if (l > r) {
            swap(l, r);
        }
        mn.query.emplace_back(l-1,r-1);
        mx.query.emplace_back(l-1,r-1);
    }

    mn.build(ls);
    mx.build(gt);

    REP (i, m) {
        cout << mx.result[i] - mn.result[i] << endl;
    }
}
