#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
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
const int iNF = 0x3f3f3f3f;
const ll MAXN = 3000006;

int t, n, m, sum, a[MAXN], mn[MAXN * 4], add[MAXN * 4], pre[MAXN * 4];
void push(int o) {
    if (add[o] != 0) {
        mn[o] += add[o];
        add[o<<1] += add[o];
        add[o<<1|1] += add[o];
        add[o] = 0;
    }
}

int get (int o) {
    return mn[o] + add[o];
}

void pull (int o) {
    mn[o] = min(get(o<<1), get(o<<1|1));
}

void build (int o, int l, int r) {
    if (l == r - 1) {
        mn[o] = pre[l];
        add[o] = 0;
    } else {
        int mid = (l + r) >> 1;
        build(o<<1, l, mid);
        build(o<<1|1, mid, r);
        add[o] = 0;
        pull(o);
    }
}

void upd (int o, int nL, int nR, int qL, int qR, int val) {
    if (nR <= qL || nL >= qR || qL >= qR) {
        /* smile */
    } else if (nL >= qL && nR <= qR) {
        add[o] += val;
    } else {
        int mid = (nL + nR) >> 1;
        push(o);
        upd(o<<1, nL, mid, qL, qR, val);
        upd(o<<1|1, mid, nR, qL, qR, val);
        pull(o);
    }
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    int testcase = 0;
    while (cin >> n) {
        cout << "Test " << ++testcase << ":" << endl;

        sum = 0;
        REP (i, n) {
            char b;
            cin >> b;
            a[i] = (b == '(' ? 1 : -1);
            sum += a[i];
            pre[i] = sum;
        }
        build(1, 0, n);

        cin >> m;
        while (m--) {
            int k;
            cin >> k;
            if (k == 0) {
                debug(sum, get(1));
                if (sum == 0 && get(1) == 0) {
                    cout << "YES" << endl;
                } else {
                    cout << "NO" << endl;
                }
            } else {
                sum += ((a[k-1] == 1) ? -2 : 2);
                upd(1, 0, n, k-1, n,((a[k-1] == 1) ? -2 : 2));
                a[k-1] = -a[k-1];
            }
        }
    }

    return 0;
}
