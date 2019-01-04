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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e6+5;
const ll MAXLG=__lg(MAXN)+2;

ll t,k;
string a,b,s;
char ans[300];
bool used[300];

bool first;
bool solvea() {
    first = true;
    REP (i,SZ(s)) {
        if (a[i] == b[i]) {
            if (ans[s[i]] == '@') {
                if (used[a[i]]) {
                    return false;
                } else {
                    ans[s[i]] = a[i];
                    used[a[i]] = true;
                }
            } else {
                if (ans[s[i]] != a[i]) {
                    return false;
                }
            }
        } else {
            if (ans[s[i]] == '@') {
                if (first) {
                    for (char j=a[i]+1;j<b[i];j++) {
                        if (!used[j]) {
                            used[j] = true;
                            ans[s[i]] = j;
                            return true;
                        }
                    }
                    if (used[a[i]]) {
                        return false;
                    } else {
                        ans[s[i]] = a[i];
                        used[a[i]] = true;
                    }
                    first = false;
                } else {
                    for (char j=a[i]+1;j<k+'a';j++) {
                        if (!used[j]) {
                            used[j] = true;
                            ans[s[i]] = j;
                            return true;
                        }
                    }
                    if (!used[a[i]]){
                        ans[s[i]] = a[i];
                        used[a[i]] = true;
                    } else {
                        return false;
                    }
                }
            } else {
                if (first) {
                    if (ans[s[i]] > a[i] && ans[s[i]] < b[i]) {
                        return true;
                    } else if (ans[s[i]] != a[i]) {
                        return false;
                    }
                    first = false;
                } else {
                    if (ans[s[i]] > a[i]) {
                        return true;
                    } else if (ans[s[i]] != a[i]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool solveb() {
    first = true;
    REP (i,SZ(s)) {
        if (a[i] == b[i]) {
            if (ans[s[i]] == '@') {
                if (used[a[i]]) {
                    return false;
                } else {
                    ans[s[i]] = a[i];
                    used[a[i]] = true;
                }
            } else {
                if (ans[s[i]] != a[i]) {
                    return false;
                }
            }
        } else {
            if (ans[s[i]] == '@') {
                if (first) {
                    for (char j=a[i]+1;j<b[i];j++) {
                        if (!used[j]) {
                            used[j] = true;
                            ans[s[i]] = j;
                            return true;
                        }
                    }
                    if (used[b[i]]) {
                        return false;
                    } else {
                        ans[s[i]] = b[i];
                        used[b[i]] = true;
                    }
                    first = false;
                } else {
                    for (char j=b[i]-1;j>='a';j--) {
                        if (!used[j]) {
                            used[j] = true;
                            ans[s[i]] = j;
                            return true;
                        }
                    }
                    if (!used[b[i]]){
                        ans[s[i]] = b[i];
                        used[b[i]] = true;
                    } else {
                        return false;
                    }
                }
            } else {
                if (first) {
                    if (ans[s[i]] > a[i] && ans[s[i]] < b[i]) {
                        return true;
                    } else if (ans[s[i]] != b[i]) {
                        return false;
                    }
                    first = false;
                } else {
                    if (ans[s[i]] < b[i]) {
                        return true;
                    } else if (ans[s[i]] != b[i]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
        cin >> k;
        cin >> s >> a >> b;
        MEM(used,0);
        REP (i,300) {
            ans[i] = '@';
        }
        if (solvea() || solveb()) {
            cout << "YES" << endl;
            queue<char> q;
            REP (i,k) {
                q.emplace(i+'a');
            }
            REP (i,k) {
                if (ans[i+'a'] == '@') {
                    while (q.size()) {
                        if (used[q.front()]) {
                            q.pop();
                        } else {
                            break;
                        }
                    }
                    cout << q.front();
                    q.pop();
                } else {
                    cout << ans[i+'a'];
                }
            }
            cout << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
