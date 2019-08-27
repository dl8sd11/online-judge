#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
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
const ll MAXN = 402;
const ll MAXC = 10000003;

typedef array<int, 4> a4;
ostream& operator << (ostream &_s,const a4 &_p){return _s<<"("<<_p[0]<<","<<_p[1]<<","<<_p[2]<<","<<_p[3]<<")";}

int n, cnt[MAXC];
a4 til[MAXN];

a4 reg (const a4 &state) {
    a4 rot[4];
    REP (i, 4) {
        REP (j, 4) {
            rot[i][j] = state[i+j >= 4 ? i+j-4 : i+j];
        }
    }

    sort(rot, rot+4);
    return rot[0];
}

int toInt (const a4 &state) {
    a4 rot = reg(state);

    ll bs = 1, sum = 0;
    REP (i, 4) {
        sum = sum + bs * rot[i];
        bs = bs * 503;
    }
    return sum % MAXC;
}

int gC (int id, int rt, int p) {
    int d = p+rt >= 4 ? p+rt-4 : p+rt;
    return til[id][d];
}

ll ans;
/********** Good Luck :) **********/
int main()
{
    IOS();

    cin >> n;
    REP (i, n) {
        REP (c, 4) {
            cin >> til[i][c];
        }
        cnt[toInt(til[i])]++;
    }
    TIME(main);

    pair<a4,int> rem[4];
    
    int ft, fb, len, hs;
    ll tot, cur;
    REP (t, n) {
        // TIME(titr);
        REP (b, n) {
            if (t == b) {
                continue;
            }
            ft = toInt(til[t]);
            fb = toInt(til[b]);
            cnt[ft]--;
            cnt[fb]--;
            REP (bd, 4) {
                {
                    // TIME(pre1);
                    rem[0].X = {til[t][3], til[t][2], gC(b, bd, 1), gC(b, bd, 0)};
                    rem[1].X = {til[t][2], til[t][1], gC(b, bd, 2), gC(b, bd, 1)};
                    rem[2].X = {til[t][1], til[t][0], gC(b, bd, 3), gC(b, bd, 2)};
                    rem[3].X = {til[t][0], til[t][3], gC(b, bd, 0), gC(b, bd, 3)};
                }

                {
                    // TIME(pre2);
                    REP (i, 4) {
                        rem[i].Y = toInt(rem[i].X);
                    }
                }
                
                {
                    // TIME(pre3);
                    sort(rem, rem + 4, [&](pair<a4,int> p1, pair<a4,int> p2) {
                        return p1.Y < p2.Y;
                    });
                }

                {
                    // TIME(cc);

                    len = 0;
                    tot = 1;
                    REP (i, 4) {
                        len++;
                        if (i == 3 || rem[i].Y != rem[i+1].Y) {
                            cur = 1;
                            hs = rem[i].Y;
                            bool alsm = rem[i].X[0] == rem[i].X[1] && rem[i].X[1] == rem[i].X[2] && rem[i].X[2] == rem[i].X[3];
                            bool dgsm = rem[i].X[0] == rem[i].X[2] && rem[i].X[1] == rem[i].X[3];
                            REP (j, len) {
                                cur *= cnt[hs] - j;
                                cur *= alsm ? 2 : 1;
                                cur *= dgsm ? 2 : 1;
                            }
                            
                            tot *= cur;
                            len = 0;
                        }
                    }

                    
                    ans += tot;
                }
                            

            }
            cnt[ft]++;
            cnt[fb]++;

        }
    }

    cout << ans/6 << endl;
    return 0;
}
