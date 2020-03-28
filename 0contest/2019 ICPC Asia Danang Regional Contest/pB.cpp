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
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 300005;
const ll MOD = 1000000007;

int n, H, r, B;
pii speed[MAXN];
ll ts[MAXN], hei[MAXN];

struct Event {
    bool type; // 0:rope, 1:banana
    int h, l, x, y; // [s, b, l1, l2], [h, l, x, y]

    bool operator < (const Event &oth) const {
        return h < oth.h;
    }
};
vector<Event> event;

void mv (int id, int tg) {
    ts[id] += speed[id].X * (tg - hei[id]);
    hei[id] = tg;
}

void swp (int x, int y, int h, int dis) {
    mv(x, h);
    mv(y, h);
    ts[x] += dis * speed[x].Y;
    ts[y] += dis * speed[y].Y;
    swap(ts[x], ts[y]);
    swap(speed[x], speed[y]);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> H >> r >> B;

    REP (i, r) {
        int b, l1, l2, s;
        cin >> b >> l1 >> l2 >> s;
        event.push_back({0,s,b,l1,l2});
    }

    REP1 (i, n) {
        cin >> speed[i].X >> speed[i].Y;
    }

    REP (i, B) {
        int l, h, x, y;
        cin >> l >> h >> x >> y;
        event.push_back({1,h,l,x,y});
    }

    sort(ALL(event));

    int ans = 0;
    for (auto E : event) {
        if (E.type) { // banana
            int id = E.l;
            mv(id, E.h);
            int rem = ts[id] % (E.x + E.y);
            if (rem >= 1 && rem <= E.x) {
                ans++;
            }
        } else {
            swp(E.x,E.y,E.h,E.l);
        }
    }

    cout << ans << endl;
}
