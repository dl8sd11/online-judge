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
const ll MAXC = 26;
const int MAXN = 102;

struct Data {
    int cnt[MAXC];
    Data() {
        MEM(cnt, 0);
    }
};

Data operator+ (const Data &d1, const Data &d2) {
    Data res;
    REP (i, MAXC) {
        res.cnt[i] = d1.cnt[i] + d2.cnt[i];
    }
    return res;
}
Data operator- (const Data &d1, const Data &d2) {
    Data res;
    REP (i, MAXC) {
        res.cnt[i] = d1.cnt[i] - d2.cnt[i];
    }
    return res;
}

Data operator* (const Data &d1, const int b) {
    Data res;
    REP (i, MAXC) {
        res.cnt[i] = d1.cnt[i]*b;
    }
    return res;
}

typedef pair<char,char> pcc;
struct Sol {
    int n;
    Data len[MAXN], rd[MAXN];
    pair<char,char> res[MAXN];

    void build() {
        Data sum;
        for (int i=(n-1)/2;i>=0;i--) {
            rd[i] = (len[i+1] - len[i]) - sum;
            sum = sum + rd[i];
            vector<int> on;
            REP (j, MAXC) {
                REP (k, rd[i].cnt[j]) {
                    on.eb(j);
                }
            }

            pary(len[i+1].cnt, len[i+1].cnt+MAXC);
            pary(len[i].cnt, len[i].cnt+MAXC);
            debug(on);

            res[i].X = on[0]+'a';
            if (SZ(on) >= 2) {
                res[i].Y = on[1]+'a';
            }
        }
    }
} solb, sols, sola;


/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    int n;
    cin >> n;
    if (n == 1) {
        cout << "? 1 1" << endl;
        string str;
        cin >> str;
        cout << "! " << str << endl;
        return 0;
    }

    {
        // build sola
        sola.n = n;
        cout << "? 1 " << n << endl;
        REP (i, (n+1)*n/2) {
            string str;
            cin >> str;
            Data nw;
            for (auto v : str) {
                nw.cnt[v-'a']++;
            }

            sola.len[SZ(str)] = sola.len[SZ(str)] + nw;
        }
        sola.build();
    }

    {
        // build solb
        solb.n= n/2;
        cout << "? 1 " << solb.n << endl;
        REP (i, (solb.n+1)*solb.n/2) {
            string str;
            cin >> str;
            Data nw;
            for (auto v : str) {
                nw.cnt[v-'a']++;
            }

            solb.len[SZ(str)] = solb.len[SZ(str)] + nw;
        }
        solb.build();
    }

    {
        // build sols
        sols.n= n/2-1;
        if (sols.n > 0) {
            cout << "? 1 " << sols.n << endl;
            REP (i, (sols.n+1)*sols.n/2) {
                string str;
                cin >> str;
                Data nw;
                for (auto v : str) {
                    nw.cnt[v-'a']++;
                }

                sols.len[SZ(str)] = sols.len[SZ(str)] + nw;
            }
            sols.build();
        }
    }

    char ans[MAXN];
    int l = 0, r = n/2-1;
    bool isL = true;
    Data R = solb.len[n/2] - sols.len[n/2-1];
    REP (i, MAXC) {
        if (R.cnt[i] > 0) {
            ans[r] = i + 'a';
            break;
        }
    }
    
    while (l < r) {
        if (isL) {
            pcc cur = solb.res[l];
            debug(cur, l, r);
            if (ans[r] == cur.X) {
                ans[l] = cur.Y;
            } else {
                ans[l] = cur.X;
            }
            r--;
        } else {
            pcc cur = sols.res[l];
            debug(cur, l, r);
            if (ans[l] == cur.X) {
                ans[r] = cur.Y;
            } else {
                ans[r] = cur.X;
            }
            l++;
        }
        isL ^= 1;
    }
    debug(ans);


    pary(sola.res, sola.res+n);
    if (n&1) {
        ans[n/2] = sola.res[n/2].X;
    }
    for (int i=0;i<n/2;i++) {

        pcc cur = sola.res[i];
        debug(i, cur);
        if (ans[i] == cur.X) {
            ans[n-1-i] = cur.Y;
        } else {
            ans[n-1-i] = cur.X;
        }
    }

    cout << "! ";
    REP (i, n) {
        cout << ans[i];
    }
    cout << endl;
    return 0;
}
/*
3
abc
a
ab
abc
b
bc
c
a
*/