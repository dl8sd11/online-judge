#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<int, ll> pli;
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
#define TIME(i) Timer i(#i)
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
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const int MAXC = 102;

int t, n;
int dis[MAXC], tran[MAXC], sm[MAXC];
int dis2[MAXC];
pair<int,int> tran2[MAXC];
vector<pair<int,int> > edg[MAXC];
string sho[MAXC], sho2[MAXC];

void pre_build_2 () {
    MEM(dis, iNF);
    dis[0] = 0;
    queue<int> bfs;
    bfs.emplace(0);

    while (!bfs.empty()) {
        int x = bfs.front();
        bfs.pop();
        for (auto v : edg[x]) {
            if (dis[x] + 1 < dis[v.X]) {
                dis[v.X] = dis[x] + 1;
                tran[v.X] = v.Y;
                bfs.emplace(v.X);
            } else if (dis[x] + 1 == dis[v.X]) {
                tran[v.X] = min(tran[v.X], v.Y);
            }
        }
    }

    { // build sho
        REP (i, 80) {
            int st = i;
            sm[i] = 0;
            while (st != 0) {
                sho[i] += tran[st] + '0';
                sm[i] += (tran[st]*tran[st]-1);
                st = st - (tran[st]*tran[st]-1);
                st %= 80;
                if (st < 0) {
                    st += 80;
                }
            }

            debug(dis2[i], sm[i], dis[i], sho[i], sho2[i]);
        }
    }
}

void pre_build () {
    { // build graph
        REP (i, 80) {
            REP1 (j, 9) {
                if (j != 1 && j != 9) {
                    int dl = j * j - 1;
                    edg[i].emplace_back((i+dl)%80, j);
                }
            }
        }
    }

    MEM(dis2, iNF);
    dis2[0] = 0;
    queue<int> bfs;
    bfs.emplace(0);

    while (!bfs.empty()) {
        int x = bfs.front();
        bfs.pop();
        for (auto v : edg[x]) {
            int w = v.Y*v.Y-1;
            if (dis2[x] + w < dis2[v.X]) {
                dis2[v.X] = dis2[x] + w;
                tran2[v.X] = {tran2[x].X+1, v.Y};
                bfs.emplace(v.X);
            } else if (dis2[x] + w == dis2[v.X]) {
                tran2[v.X] = min(tran2[v.X], pii(tran2[x].X+1, v.Y));
            }
        }
    }

    { // build sho
        REP (i, 80) {
            int st = i;
            int sm = 0;
            while (st != 0) {
                sho2[i] += tran2[st].Y + '0';
                sm += (tran2[st].Y*tran2[st].Y-1);
                st = st - (tran2[st].Y*tran2[st].Y-1);
                st %= 80;
                if (st < 0) {
                    st += 80;
                }
            }
        }
    }
}

struct Ans {
    int ones, nines;
    string mid;
    bool better (const Ans &oth) const {
        if (ones != oth.ones) {
            return ones > oth.ones;
        } else {
            string s1 = mid + "9";
            string s2 = oth.mid + "9";
            return s1 < s2;
        }
    }

    void operator = (const Ans &oth) {
        ones = oth.ones;
        mid = oth.mid;
        nines = oth.nines;
    }

    Ans (int dl, string md) {
        nines = dl / 80;
        mid = md;
        ones = n - nines - SZ(md);
    }

    Ans() {

    }
};
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    cin >> t;

    pre_build();
    pre_build_2();

    while (t--) {
        cin >> n;
        Ans ans;
        ans.ones = -1;
        
        for (int i=1; i*i<=81*n; i++) {
            int k = i*i;
            if (k >= n) {
                int dl = k - n;
                if (dl >= dis2[dl % 80]) {
                    debug(k);
                    if (dl < sm[dl % 80]) {
                        Ans cur(dl, sho2[dl%80]);
                        if (cur.better(ans)) {
                            debug(cur.ones, cur.mid, cur.nines);
                            ans = cur;
                        }
                    } else {
                        Ans cur(dl, sho[dl%80]);
                        if (cur.better(ans)) {
                            debug(cur.ones, cur.mid, cur.nines);
                            ans = cur;
                        }
                    }
                }
            }
        }

        debug(ans.ones, ans.mid, ans. nines);

        if (ans.ones < 0) {
            cout << -1 << endl;
        } else {
            int tot = 0;
            REP (i, ans.ones) {
                cout << 1;
                tot += 1;
            }
            for (auto c : ans.mid) {
                tot += SQ(c-'0');
                cout << c;
            }
            REP (i, ans.nines) {
                cout << 9;
                tot += 81;
            }
            cout << endl;
            debug(tot);
        }


    }
    return 0;
}
