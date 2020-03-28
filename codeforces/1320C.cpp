#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define pb push_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x)
{
    cerr<<x<<endl;
}
template<typename T, typename ...S> void _do(T &&x, S &&...y)
{
    cerr<<x<<", ";
    _do(y...);
}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg; it!=ed; it++)
    {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v)
{
    return _printRng(os,v.begin(), v.end());
}
template<typename T> void pary(T bg, T ed)
{
    _printRng(cerr,bg,ed);
    cerr<<endl;
}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1000006;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, p;

typedef array<int,3> Monster; // attack, defense, cost
typedef array<int,2> item;    // attack/defense cost

vector<Monster> monster;
vector<item> wep, arm;

ll seg[MAXN*4], a[MAXN], tag[MAXN*4];

ll get (int o) {
    return seg[o] + tag[o];
}

void push (int o) {
    if (tag[o]) {
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        seg[o] += tag[o];
        tag[o] = 0;
    }
}

void pull (int o) {
    seg[o] = max(get(o<<1), get(o<<1|1));
}

void build (int o, int l, int r) {
    if (l == r - 1) {
        seg[o] = a[l];
    } else {
        int mid = (l + r) >> 1;
        build(o<<1, l, mid);
        build(o<<1|1, mid, r);
        pull(o);
    }
}

void add (int qL, int qR, int val, int o, int nL, int nR) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o] += val;
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        add(qL, qR, val, o<<1, nL, nM);
        add(qL, qR, val, o<<1|1, nM, nR);
        pull(o);
    }
}

/*********************GoodLuck***********************/
int main ()
{
    IOS();

    cin >> n >> m >> p;

    REP (i, n)
    {
        wep.pb({0, 0});
        cin >> wep.back()[0] >> wep.back()[1];
    }

    REP (i, m)
    {
        arm.pb({0, 0});
        cin >> arm.back()[0] >> arm.back()[1];
    }

    REP (i, p)
    {
        monster.pb({0, 0, 0});
        REP (j, 3)
        {
            cin >> monster.back()[j];
        }
    }

    fill(a,a+MAXN,-INF);
    debug(a[0]);
    for (auto el : arm) {
        a[el[0]] = max(a[el[0]], ll(-el[1]));
        debug(a[el[0]]);
    }

    build(1, 0, MAXN);

    sort(ALL(wep));
    sort(ALL(monster));

    int idx = 0;

    ll ans = -INF;
    for (auto v : wep) {
        while (idx < p && monster[idx][0] < v[0]) {
            add(monster[idx][1]+1, MAXN, monster[idx][2], 1, 0, MAXN);
            debug(monster[idx][1]);
            idx++;
        }

        debug(get(1), v[1]);
        ll cur = get(1) - v[1];
        ans = max(ans, cur);
    }

    cout << ans << endl;
}
