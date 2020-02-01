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
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 51;

int n, m;
int car[4][MAXN];
vector<int> ot;
vector<pair<int, pii> > opt;

void wrt (int ca, int r, int c) {
    opt.eb(ca, pii(r, c));
}

pii ck (int r, int c) {
    int nr = r, nc = c;
    if (r == 1 && c == n-1) {
        nr++;
    } else if (r == 2 && c == 0) {
        nr--;
    } else if (r == 1) {
        nc++;
    } else {
        nc--;
    }

    if (car[nr][nc] == 0){
        wrt(car[r][c], nr, nc);
        swap(car[nr][nc], car[r][c]);
        return {nr, nc};
    } else {
        return {r, c};
    }
}

pii pos[MAXN*2];

void chk () {
    REP (i, n) {
        for (auto j : {1,2}) {
            int k = j == 1 ? 0 : 3;
            if (car[j][i] && car[j][i] == car[k][i]) {
                debug(ot, car[j][i]);
                ot.erase(find(ALL(ot), car[j][i]));
                wrt(car[j][i], k, i);
                car[j][i] = car[k][i] = 0;
            }
        }
    }
}

void allck() {
    for (auto c : ot) {
        pos[c] = ck(pos[c].X, pos[c].Y);
    }
    debug("---------");
    REP (i ,4) {
        pary(car[i], car[i]+n);
    }
    debug("---------");
    chk();
    debug("---------");
    REP (i ,4) {
        pary(car[i], car[i]+n);
    }
    debug("---------");
}

void arg () {
    REP1 (i, SZ(ot) - 1) {
        int r, c;
        tie(r, c) = pos[ot[i]];
        while (true) {
            int tr = r, tc = c;
            tie(r, c) = ck(r, c);
            if (tr == r && tc == c) {
                break;
            }
        }
        pos[ot[i]] = pii(r, c);
    }
}


/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n >> m;
    REP (i, 4) {
        REP (j, n) {
            cin >> car[i][j];
        }
    }

    RREP (i, n-1) {
        if (car[1][i] && car[0][i] == car[1][i]) {
            wrt(car[1][i], 0, i);
            car[0][i] = 0;
            car[1][i] = 0;
        } else if (car[1][i]) {
            ot.eb(car[1][i]);
            pos[car[1][i]] = {1, i};
        }
    }

    REP (i, n) {
        if (car[2][i] && car[3][i] == car[2][i]) {
            wrt(car[2][i], 3, i);
            car[2][i] = 0;
            car[3][i] = 0;
        } else if (car[2][i]) {
            ot.eb(car[2][i]);
            pos[car[2][i]] = {2, i};
        }
    }

    if (ot.size() == n*2) {
        cout << -1 << endl;
    } else {

        arg();
        while (ot.size()) {
            allck();            
        }

        cout << opt.size() << endl;
        for (auto o : opt) {
            cout << o.X << " " << o.Y.X+1 << " " << o.Y.Y+1 << endl;
        }
    }
    return 0;
}
