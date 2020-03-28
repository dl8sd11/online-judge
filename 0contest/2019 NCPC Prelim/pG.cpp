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

const int MAXN = 100005;
const ll MOD = 1000000007;

int t, n, in[27], out[27];
string str[MAXN];

vector<int> edge[27];

vector<int> ans;

int cur[27];
void dfs (int nd) {
    for (int &i=cur[nd]; i<SZ(edge[nd]);) {
        int id = edge[nd][i];
        const string &v = str[edge[nd][i++]];
        dfs(v.back()-'a');
        ans.eb(id);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;

    while (t--) {
        cin >> n;

        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        memset(cur, 0, sizeof(cur));
        ans.clear();
        REP (i, 26) {
            edge[i].clear();
        }

        REP (i, n) {
            cin >> str[i];
            edge[str[i][0]-'a'].eb(i);
            out[str[i][0]-'a']++;
            in[str[i].back()-'a']++;
        }

        int stc = 0, edc = 0, st = 0;
        bool noAns = false;

        REP (i, 26) {
            sort(ALL(edge[i]), [&](int k, int j) {
                return str[k] < str[j];
            });


            if (in[i] != out[i]) {
                if (in[i] - out[i] == 1) {
                    edc++;
                } else if (out[i] - in[i] == 1) {
                    stc++;
                    st = i;
                } else {
                    noAns = true;
                }
            }
        }

        if (stc != 0 || edc != 0) {
            if (stc != 1 || edc != 1) {
                noAns = true;
            }
        }

        if (noAns) {
        } else {
            cout << "IMPOSSIBLE" << endl;
            dfs(st);
            debug(ans);

            if (ans.size() == n) {
                for (int i=n-1;i>=0;i--) {
                    if (i == 0) {
                        cout << str[ans[i]] << endl;
                    } else {
                        int sz = SZ(str[ans[i]]);
                        for (int j=0;j<sz-1;j++) {
                            cout << str[ans[i]][j];
                        }
                    }
                }
            } else {
                cout << "IMPOSSIBLE" << endl;
            }

        }
    }

}
/*
3
3
eve
eagle
age
4
ago
oh
home
ema
2
ago
dig
*/
