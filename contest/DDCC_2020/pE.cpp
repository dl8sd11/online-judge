#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=(k) ; i-=in)
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
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 202;

int n, ac;
vector<int> genBin () {
    vector<int> vec;
    REP (i, n) {
        vec.emplace_back(0);
    }
    REP (i, n) {
        vec.emplace_back(1);
    }
    random_shuffle(vec.begin(), vec.end());
    return vec;
}

set<vector<int> > qry;
vector<int> rans;
pair<int,int> ball[MAXN];
char ans[MAXN];

string check (vector<int> idx) {
    int red = 0;
    for (auto d : idx) {
        red += rans[d];
    }
    return red > n/2 ? "Red" : "Blue";
}

void submit () {
    REP1 (i, n*2) {
        if ((rans[i-1] && ans[i] == 'B') || (!rans[i-1] && ans[i] == 'R')) {
            return;
        }
    }
    ac++;
}

void query () {
    for (auto q : qry) {
        vector<int> nw;
        REP (i, n*2) {
            if (q[i]) {
                nw.emplace_back(i);
            }
        }

#ifndef tmd
        cout << "?";
        for (auto v : nw) {
            cout << " " << v+1;
        }
        cout << endl;
#endif

        string res;
#ifdef tmd
        res = check(nw);  
#else
        cin >> res;
#endif
        for (auto v : nw) {
            ball[v+1].first += (res == "Red" ? 1 : -1);
        }
    }
}

void srt () {
    sort(ball+1, ball+n*2+1);
    vector<int> tg;
    REP (i, n/2) {
        tg.emplace_back(ball[i+1].second);
        tg.emplace_back(ball[n*2-i].second);
    }
    tg.emplace_back(ball[n].second);
    debug(tg);

#ifndef tmd
        cout << "?";
        for (auto v : tg) {
            cout << " " << v+1;
        }
        cout << endl;
#endif

    string res;
#ifdef tmd
        res = check(tg);  
#else
        cin >> res;
#endif 

    REP (i, n/2) {
        ball[i+1].first += (res == "Red" ? 1 : -1);
        ball[n*2-i].first += (res == "Red" ? 1 : -1);
    }
    ball[n].first += (res == "Red" ? 1 : -1);

}

void output () {
    sort(ball+1, ball+n*2+1);
    REP1 (i, n) {
        ans[ball[i].second] = 'B';
        ans[ball[i+n].second] = 'R';
    }
    cout << "! ";
    REP1 (i, n*2) {
        cout << ans[i];
    }
    cout << endl;

#ifdef tmd
    submit();
#endif
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    srand(time(0));

    cin >> n;

    ac = 0;
        REP1 (i, n*2) {
            ball[i].first = 0;
            ball[i].second = i;
        }

        rans = genBin();
        qry.clear();
        
        REP (i, 100) {
            int tk = 0;
            while (true) {
                vector<int> cur = genBin();
                if (qry.count(cur) == 0) {
                    qry.insert(cur);
                    break;
                }
                if (tk++ == 100) {
                    break;
                }
            }
            if (tk == 101) {
                break;
            }
        }
        query();

        REP (i, 110) {
            srt();
        }

        output();



    return 0;
}
