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
template<typename T> ostream& operator << (ostream &os, pair<T,T> &p) {
    return os<<"{"<<p.X<<","<<p.Y<<"}";
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const ll MOD = 1000000007;

vector<set<int> > row, col;
int n, m;
vector<vector<int> > s, nei, cnt;

void update(int x, int y, int val) {
    cnt[x][y] += (val > 0 ? 1 : -1);
    nei[x][y] += val;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    
    int t;
    cin >> t;
    REP1 (tc, t) {
        cout << "Case #" << tc << ": ";

        cin >> n >> m;

        s.clear();
        nei.clear();
        cnt.clear();

        ll sum = 0;

        row.clear();
        col.clear();
        REP (i, n) {
            vector<int> cur;
            REP (j, m) {
                
                int tp;
                cin >> tp;
                cur.eb(tp);

                sum += tp;
            }
            s.emplace_back(cur);
            cnt.eb(vector<int>(m, 0));
            nei.eb(vector<int>(m, 0));
        }

        REP (i, n) {
            REP (j, m) {

                if (i) {
                    cnt[i-1][j]++;
                    nei[i-1][j]+=s[i][j];
                }
                if (i<n-1) {
                    cnt[i+1][j]++;
                    nei[i+1][j]+=s[i][j];
                }

                if (j) {
                    cnt[i][j-1]++;
                    nei[i][j-1]+=s[i][j];
                }
                if (j<m-1) {
                    cnt[i][j+1]++;
                    nei[i][j+1]+=s[i][j];
                }

            }
        }

        REP (i, n) {
            set<int> cur;
            REP (j, m) {
                cur.insert(j);
            }
            row.eb(cur);
        }

        REP (j, m) {
            set<int> cur;
            REP (i, n) {
                cur.insert(i);
            }
            col.eb(cur);
        }

        vector<pii> cque, nque;
        REP (i, n) {
            REP (j, m) {
                if (s[i][j] * cnt[i][j] < nei[i][j]) {
                    nque.eb(i, j);
                }
            }
        }

        ll ans = 0;
        while (true) {

            ans += sum;

            swap(cque, nque);

            sort(ALL(cque), [&](pii &p1, pii &p2) {
                    return s[p1.X][p1.Y] > s[p2.X][p2.Y];
                    });

            if (cque.empty()) {
                break;
            }

            debug(s);
            debug(cque);
            nque.clear();

            vector<pii> check;
            for (auto pos : cque) {

                int x, y;
                tie(x, y) = pos;

                if (s[x][y] != 0) {

                    int xp=-1, xn=-1;
                    auto xpp = row[x].lower_bound(y);
                    if (xpp != row[x].begin()) {
                        xp = *prev(xpp);
                    }

                    if (xpp != prev(row[x].end())) {
                        xn = *next(xpp);
                    }

                    if (xp != -1) {
                        check.eb(x, xp);
                        update(x, xp, -s[x][y]);
                        if (xn != -1) {
                            update(x, xn, s[x][xp]);
                        }
                    }
                    if (xn != -1) {
                        check.eb(x, xn);
                        update(x, xn, -s[x][y]);
                        if (xp != -1) {
                            update(x, xp, s[x][xn]);
                        }
                    }
                
                    int yp=-1, yn=-1;
                    auto ypp =col[y].lower_bound(x);
                    if (ypp != col[y].begin()) {
                        yp = *prev(ypp);
                    }
                    if (ypp != prev(col[y].end())) {
                        yn = *next(ypp);
                    }

                    if (yp != -1) {
                        update(yp, y, -s[x][y]);
                        check.eb(yp, y);
                        if (yn != -1) {
                            update(yn, y, s[yp][y]);
                        }
                    }
                    if (yn != -1) {
                        update(yn, y, -s[x][y]);
                        check.eb(yn, y);
                        if (yp != -1) {
                            update(yp, y, s[yn][y]);
                        }
                    }
                
                    col[y].erase(x);
                    row[x].erase(y);
                    sum -= s[x][y];
                    s[x][y] = 0;
                }

            }

            sort(ALL(check));
            check.resize(unique(ALL(check))-check.begin());
            debug(check);
            for (auto v : check) {
                debug(v.X, v.Y, cnt[v.X][v.Y], nei[v.X][v.Y]);
                if (s[v.X][v.Y] != 0 && s[v.X][v.Y] * cnt[v.X][v.Y] < nei[v.X][v.Y]) {
                    nque.eb(v);
                }
            }

        }

        cout << ans << endl;
    }

}

