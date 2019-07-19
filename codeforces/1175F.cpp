#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
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
const ll MAXN = 300005;
const ll MAXLG = __lg(MAXN) + 3;

int n, a[MAXN], st[MAXLG][MAXN], u[MAXN], lst[MAXN];
ll ans;

int query(int l,int r) {
    int e = __lg(r-l+1);
    return max(st[e][l], st[e][r-(1<<e)+1]);
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> a[i];
    }

    REP (t,2) {
        MEM(lst,-1);
        u[0] = 0;
        st[0][0] = a[0];
        lst[a[0]] = 0;
        REP1 (i,n-1) {
            st[0][i] = a[i];
            u[i] = max(u[i-1], lst[a[i]]+1);
            lst[a[i]] = i;
        }
        pary(a,a+n);
        pary(u,u+n);

        REP1 (i, MAXLG-1) {
            REP (j,n) {
                if (j + (1<<i) <= n) {
                    st[i][j] = max(st[i-1][j],st[i-1][j+(1<<i-1)]);
                }
            }
        }

        REP (i,n) {
            if (a[i] == 1) {
                int len = 1;
                for (int j=i+1;j<n;j++) {
                    if (a[j] == 1) {
                        break;
                    }
                    len = max(a[j], len);
                    if (u[j] <= j-len+1 && query(j-len+1,j) == len) {
                        ans++;
                        debug(i,j,len);
                    }
                }
            }
        }
        debug("rev");
        reverse(a,a+n);
    }

    REP (i,n) {
        if (a[i] == 1) {
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}
