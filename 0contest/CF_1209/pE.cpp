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
    // const ll MAXN = 
     
    int t, n, m;
    int a[13][2003];
    /********** Good Luck :) **********/
    int main () {
        TIME(main);
        IOS();
     
        cin >> t;
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        while (t--) {
            cin >> n >> m;
            REP (i, n) {
                REP (j, m) {
                    cin >> a[i][j];
                }
            }
     
            vector<pii> c;
            REP (j, m) {
                int mx = 0;
                REP (i, n) {
                    mx = max(mx, a[i][j]);
                }
                c.eb(mx, j);
            }
     
            sort(ALL(c));
     
            vector<int> perm;
     
            int can = min(n,m);
            REP (i, can) {
                perm.eb(c[m-1-i].Y);
            }
            REP (i, n-can) {
                perm.eb(-1);
            }
            sort(ALL(perm));
     
            ll ans = 0;
            int rm[13];

            REP (u, 100005) {
                shuffle(perm.begin()+1, perm.end(), rng);
                MEM(rm, 0);
                REP (pd, n) {
                    if (perm[pd] == -1) {
                        continue;
                    }
                    int sft = 0;
                    REP (i, n) {
                        if (a[i][perm[pd]] > a[sft][perm[pd]]) {
                            sft = i;
                        }    
                    }
     
                    REP (i, n) {
                        int p = (i +sft) % n;
                        rm[(pd+i)>=n?(pd+i)-n:pd+i] = max(rm[(pd+i)>=n?(pd+i)-n:pd+i], a[p][perm[pd]]);
                    }
                }
     
                ll cur = 0;
                REP (i, n) {
                    cur += rm[i];
                }
     
                ans = max(ans, cur);
            } 
     
            cout << ans << endl;
        }
        return 0;
    }/**********Meow***********/
