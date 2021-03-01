#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
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
const ll MAXN = 300005;

int n, t[MAXN], id[MAXN];
ll tSum, sSum;
pii s[MAXN];
pair<pii, int> pos[MAXN], neg[MAXN];
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> s[i].X;
        sSum += s[i].X;
        s[i].Y = i + 1;
    }

    REP (i, n) {
        cin >> t[i];
        tSum += t[i];
    }

    sort(s, s+n);
    sort(t, t+n);

    if (tSum != sSum) {
        cout << "NO" << endl;
    } else {
        int pCnt = 0, nCnt = 0;
        vector<pair<pii, int> > ans;
        ans.reserve(MAXN);

        REP (i, n) {
            if (s[i].X > t[i]) {
                pos[pCnt++] = {pii(s[i].X, s[i].X - t[i]), s[i].Y};
            } else if (s[i].X < t[i]) {
                neg[nCnt++] = {pii(s[i].X, t[i] - s[i].X), s[i].Y};
            }
        }

        sort(pos, pos + pCnt);
        sort(neg, neg + nCnt);

        while (pCnt && nCnt) {
            auto &pB = pos[pCnt - 1].X, &nB = neg[nCnt - 1].X;
            if (pB.X < nB.X) {
                break;
            }
            int mn = min(pB.Y, nB.Y);
            int len = pB.X - nB.X;
            if (mn > len / 2) {
                break;
            }
            
            ans.eb(pii(neg[nCnt - 1].Y, pos[pCnt - 1].Y), mn);
            if (pB.Y < nB.Y) {
                pCnt--;
                nB.Y -= mn;
            } else if (pB.Y > nB.Y) {
                nCnt--;
                pB.Y -= mn;
            } else {
                pCnt--, nCnt--;
            }
        }
        debug(pCnt, nCnt);

        if (pCnt + nCnt == 0) {
            cout << "YES" << endl;
            cout << SZ(ans) << endl;
            for (auto p : ans) {
                cout << p.X.X << " " << p.X.Y << " " << p.Y << endl;
            }
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
