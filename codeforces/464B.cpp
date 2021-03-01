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
const double eps = 1e-9;
// const ll MAXN = 

vector<vector<int>> vec[8];
int sel[8];

double len(vector<ll> &v) {
    return sqrt(ll(v[0])*v[0]+v[1]*v[1]+v[2]*v[2]);
}
bool cube() {
    vector<int> v[8];
    REP (i,8) {
        v[i] = vec[i][sel[i]];
    }
    sort(v,v+8);
    if (unique(v,v+8)-v < 8) {
        return false;
    }
    vector<vector<ll>> sub;
    REP (i,8) {
        sub.clear();
        REP (j,8) {
            vector<ll> cur(3);
            REP (k,3) {
                cur[k] = v[j][k]-v[i][k];
            }
            if (i != j) {
                if (sub.empty() || len(sub.front()) - len(cur) > eps) {
                    sub.clear();
                    sub.eb(cur);
                } else if ( abs(len(sub.front()) - len(cur)) < eps) {
                    sub.eb(cur);
                }
            }
        }
        if (sub.size() != 3) {
            return false;
        } else {
            REP (x,3) {
                REP (y,3) {
                    if (x != y) {
                        ll sum = 0;
                        REP (k,3) {
                            sum += ll(sub[x][k])*sub[y][k];
                        }
                        if (sum != 0) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}
void dfs(int idx) {
    if (idx == 7) {
        if (cube()) {
            cout << "YES" << endl;
            REP (i,8) {
                REP (j,3) {
                    cout << vec[i][sel[i]][j] << " \n"[j==2];
                }
            }
            exit(0);
        } else {
            return;
        }
    }
    REP (i,SZ(vec[idx])) {
        sel[idx] = i;
        dfs(idx+1);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    REP (i,8) {
        vector<int> tmp;
        REP (j,3) {
            ll num;
            cin >> num;
            tmp.eb(num);
        }
        sort(ALL(tmp));
        do {
            vec[i].eb(tmp);
        } while(next_permutation(ALL(tmp)));
    }

    dfs(0);
    cout << "NO" << endl;
    return 0;
}