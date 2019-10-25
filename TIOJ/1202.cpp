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
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

int n;
multiset<int> h;
struct Query {
    int x, hei;
    bool add;

    bool operator < (const Query &q) const {
        if (x != q.x) {
            return x < q.x;
        } else {
            return add > q.add;
        }
    }
};
vector<Query> qry;
/*********************GoodLuck***********************/
int main () {
    IOS();

    while(cin >> n && n) {
        qry.clear();
        h.clear();
        REP (i, n) {
            int l, h, r;
            cin >> l >> h >> r;
            qry.push_back({l, h, 1});
            qry.push_back({r, h, 0});
        }

        sort(qry.begin(), qry.end());


        int lst = -1;
        vector<pair<int,int> > ans;
        REP (i, SZ(qry)) {
            int x = qry[i].x;
            while (qry[i].x == x) {
                if (qry[i].add) {
                    h.insert(qry[i].hei);
                } else {
                    h.erase(h.find(qry[i].hei));
                }
                i++;
            }
            i--;
            int cur = h.empty() ? 0 : *prev(h.end());
            if (cur != lst) {
                ans.emplace_back(x, cur);
                lst = cur;
            }
        }

        bool fist = 1;
        for (auto p : ans) {
            if (!fist) {
                cout << " ";
            }
            fist = 0;
            cout << p.first << " " << p.second;
        }
        cout << endl;
    }

    return 0;
}
