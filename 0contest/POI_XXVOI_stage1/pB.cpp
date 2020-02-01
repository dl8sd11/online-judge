#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
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
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 500003;

ll n;
pair<ll,pii> dis[MAXN];
map<ll,ll> node;
struct Edge {
    ll u,v,w;
};
vector<Edge> edge;

void nie () {
    edge.clear();
    REP (i,n-2) {
        if (abs(dis[i].Y.X - dis[i].Y.Y) == 0 || abs(dis[i].Y.X - dis[i].Y.Y) != abs(dis[0].Y.X - dis[0].Y.Y)) {
            cout << "NIE" << endl;
            exit(0);
        }
    }
    edge.push_back({1,n,abs(dis[0].Y.X - dis[0].Y.Y)});
    REP (i,n-2) {
        if (dis[i].Y.X > dis[i].Y.Y) {
            edge.push_back({dis[i].X,n,dis[i].Y.X - abs(dis[0].Y.X - dis[0].Y.Y)});
        } else {
            edge.push_back({dis[i].X,1,dis[i].Y.Y - abs(dis[0].Y.X - dis[0].Y.Y)});
        }
    }


    cout << "TAK" << endl;
    assert(edge.size() == n-1);
    for (auto e : edge) {
        assert(e.w > 0);
        cout << e.u << " " << e.v << " " << e.w << endl;
    }
    exit(0);

}
void valid(ll val) {
    if (node.find(val) != node.end()) {
        nie();
    }
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    assert(n>1);
    if (n == 2) {
        cout << "TAK" << endl;
        cout << "1 2 3" << endl;
        return 0;    
    }
    REP (i,n-2) {
        cin >> dis[i].Y.X;
        assert(dis[i].Y.X > 0);
    }
    REP (i,n-2) {
        dis[i].X = i+2;
        cin >> dis[i].Y.Y;
        assert(dis[i].Y.Y > 0);
    }
    sort(dis,dis+n-2,[&](pair<ll,pii> a,pair<ll,pii> b){return a.Y.X+a.Y.Y < b.Y.X+b.Y.Y;});

    dis[n-2] = {1,{0,dis[0].Y.X+dis[0].Y.Y}};
    dis[n-1] = {n,{dis[0].Y.X+dis[0].Y.Y,0}};
    ll ptr = n;
    
    node[-(dis[0].Y.X+dis[0].Y.Y)] = n-2;
    node[dis[0].Y.X+dis[0].Y.Y] = n-1;
    REP (i,n-2) {
        if (dis[i].Y.X+dis[i].Y.Y != dis[0].Y.X+dis[0].Y.Y) {
            ptr = i;
            break;
        }
        valid(dis[i].Y.X-dis[i].Y.Y);
        node[dis[i].Y.X-dis[i].Y.Y] = i;
    }

    ll pr = -1;
    for (auto it=node.begin();it!=node.end();it++) {
        ll cur = (*it).Y;
        if (it != node.begin()) {
            ll d = dis[cur].Y.X - dis[pr].Y.X;
            debug(dis[cur].X,dis[pr].X,d);
            edge.push_back({dis[cur].X,dis[pr].X,d});
        }
        pr = cur;
    }

    for (ll i=ptr;i<n-2;i++) {
        auto ret = node.find(dis[i].Y.X-dis[i].Y.Y);
        if (ret == node.end()) {
            nie();
        } else {
            ll d = dis[i].Y.X + dis[i].Y.Y - dis[0].Y.X - dis[0].Y.Y >> 1;
            edge.push_back({dis[i].X,dis[(*ret).Y].X,d});
        }
    }

    cout << "TAK" << endl;
    assert(edge.size() == n-1);
    for (auto e : edge) {
        assert(e.w > 0);
        cout << e.u << " " << e.v << " " << e.w << endl;
    }
    return 0;
}
