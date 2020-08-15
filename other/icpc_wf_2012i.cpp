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
template<typename T> ostream &operator << (ostream &os,const vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> ostream &operator << (ostream &os,const array<T,3> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1000006;
const ll MOD = 1000000007;

vector<pair<int,int> > row[MAXN], col[MAXN];

struct Segment {
    vector<array<int,3> > vert;
    vector<array<int,3> > hori;
};

void ord (vector<array<int,3> > &vec) {
    for (auto &ar : vec) {
        if (ar[1] > ar[2]) {
            swap(ar[1], ar[2]);
        }
    }
}

int r, c, m, n;
pii build (int x, int y, int dir, Segment &seg) {
    while (true) {
        int nx, ny;
        //debug(x, y);
        bool flag = false;
        int pd = dir;
        if (dir == 0) {
            auto ptr = lower_bound(ALL(col[y]), pii(x, -1));
            ny = y;
            if (col[y].empty() || ptr == col[y].begin()) {
                nx = -1;
                flag = true;
            } else {
                nx = prev(ptr)->X;
                dir = prev(ptr)->Y == 0 ? 1 : 3;
            }
        } else if (dir == 1) {
            auto ptr = upper_bound(ALL(row[x]), pii(y, 3));
            nx = x;
            if (row[x].empty() || ptr == row[x].end()) {
                ny = c;
                flag = true;
            } else {
                ny = ptr->X;
                dir = ptr->Y == 0 ? 0 : 2;
            }
        } else if (dir == 2) {
            auto ptr = upper_bound(ALL(col[y]), pii(x, 3));
            ny = y;
            if (col[y].empty() || ptr == col[y].end()) {
                nx = r;
                flag = true;
            } else {
                nx = ptr->X;
                dir = ptr->Y == 1 ? 1 : 3;
            }
        } else if (dir == 3) {
            auto ptr = lower_bound(ALL(row[x]), pii(y, -1));
            nx = x;
            if (row[x].empty() || ptr == row[x].begin()) {
                ny = -1;
                flag = true;
            } else {
                ny = prev( ptr )->X;
                dir = prev( ptr )->Y == 1 ? 0 : 2;
            }
        }
        if (pd & 1) {
            seg.hori.push_back({x, y, ny});
        } else {
            seg.vert.push_back({y, x, nx});
        }
        //debug(x, y, nx, ny);
        x = nx;
        y = ny;
        if (flag) {
            break;
        }
    }
    ord(seg.hori);
    ord(seg.vert);

    return {x, y};
}

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

pair<ll, pii> solve (Segment seg) {
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> rk;
    vector<array<int,3> > qry;
    for (auto v : seg.hori) {
        qry.push_back({v[1]+1, -2, v[0]});
        qry.push_back({v[2], -1, v[0]});
    }

    for (auto v : seg.vert) {
        qry.push_back({v[0], v[1]+1, v[2]-1});
    }

    sort(ALL(qry));
    ll sum = 0;
    pii mn = {MOD, MOD};
    for (auto q : qry) {
        debug(q);
        if (q[1] == -2) {
            rk.insert(q[2]*2);
        } else if (q[1] == -1) {
            rk.erase(q[2]*2);
        } else {
            int cur = max(0, int(rk.order_of_key(q[2]*2+1) - rk.order_of_key(q[1]*2-1)));

            debug(cur);
            if (cur > 0) {
                mn = min(mn, pii(*rk.lower_bound(q[1]*2)/2, q[0]));
            }
            sum += cur;
        }
    }

    return {sum, mn};
}
/*********************GoodLuck***********************/
int main () {
    IOS();


    int cno = 0;
    while (cin >> r >> c >> m >> n) {
        for (int i=0; i<r; i++) {
            row[i].clear();
        }
        for (int i=0; i<c; i++) {
            col[i].clear();
        }
        for (int i=0; i<m; i++) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            row[x].eb(y, 0);
            col[y].eb(x, 0);
        }

        for (int i=0; i<n; i++) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            row[x].eb(y, 1);
            col[y].eb(x, 1);
        }

        for (int i=0; i<r; i++) {
            sort(ALL(row[i]));
        }
        for (int i=0; i<c; i++) {
            sort(ALL(col[i]));
        }

        Segment in, out;
        pii end = build(0, -1, 1, in);
        build(r-1, c, 3, out);
        //debug(end.X, end.Y);

        debug(in.hori);
        debug(in.vert);

        debug(out.hori);
        debug(out.vert);

        cout << "Case " << (++cno )<<  ": ";
        if (end == pii(r-1, c)) {
            cout << 0 << endl;
            continue;
        }

        swap(in.vert, out.vert);

        pair<ll, pii> rin = solve(in), rout = solve(out);
        pii mn = min(rin.Y, rout.Y);
        if (rin.X + rout.X == 0) {
            cout << "impossible" << endl;
        } else {
            cout << rin.X + rout.X << " " << mn.X+1 << " " << mn.Y+1 << endl;
        }

    }

}

