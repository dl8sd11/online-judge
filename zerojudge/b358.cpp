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
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;
ll n,a,b;
pdd pt[105];
struct Line {
    pdd p,t;
};
double area[105];
pdd cmpp;
/********** Good Luck :) **********/
int main()
{
    IOS();
    ll cs = 0;
    while (cin >> n >> a >> b) {
        cs++;
        REP (i,n) {
            cin >> pt[i].X >> pt[i].Y;
        }

        REP (i,n) {
            debug(i);
            vector<Line> bisector;
            // build bisector
            REP (j,n) if (i != j) {
                bisector.pb({{(pt[i].X+pt[j].X)/2,(pt[i].Y+pt[j].Y)/2},{pt[i].Y-pt[j].Y,pt[j].X-pt[i].X}});
            }

            bisector.pb({{0,0},{0,-1}});
            bisector.pb({{0,0},{1,0}});
            bisector.pb({{a,b},{-1,0}});
            bisector.pb({{a,b},{0,1}});
            
            debug(SZ(bisector));
            vector<pdd> vorov;
            REP (k,SZ(bisector)) {
                REP (j,k) {
                    Line b1 = bisector[k];
                    Line b2 = bisector[j];
                    double det = b2.t.X*b1.t.Y-b1.t.X*b2.t.Y;
                    double detx = (b2.p.Y-b1.p.Y)*b2.t.X-(b2.p.X-b1.p.X)*b2.t.Y;
                    if (det != 0) {
                        pdd np = {b1.p.X+detx/det*b1.t.X,b1.p.Y+detx/det*b1.t.Y};
                        // if (np.X == 0 && np.Y == 3) {
                        //     debug(b1.p,b1.t);
                        //     debug(b2.p,b2.t);
                        // }
                        bool flag = true;
                        REP (l,SZ(bisector)) {
                            Line b3 = bisector[l];
                            pdd t2 = {np.X-b3.p.X,np.Y-b3.p.Y};
                            double cross = b3.t.X*t2.Y - b3.t.Y*t2.X;
                            if (cross < -1e-8) {
                                // debug(np);
                                // debug(b3.p,b3.t);
                                // debug(cross);
                                flag = false;
                                break;
                            }
                        }

                        if (flag) {
                            vorov.pb(np);
                        }
                    }
                }
            }
            cmpp = pt[i];
            debug(cmpp);
            sort(vorov.begin(),vorov.end(),[](const pdd &p1,const pdd &p2){
                if (p1.X -cmpp.X> 0) {
                    if (p2.X-cmpp.X> 0) {
                        return (cmpp.Y-p1.Y)/(cmpp.X-p1.X) > (cmpp.Y-p2.Y)/(cmpp.X-p2.X);
                    } else {
                        return true;
                    }
                } else {
                    if (p2.X-cmpp.X > 0) {
                        return false;
                    } else {
                        return (cmpp.Y-p1.Y)/(cmpp.X-p1.X) > (cmpp.Y-p2.Y)/(cmpp.X-p2.X);
                    }
                }
            });
            vorov.resize(unique(ALL(vorov))-vorov.begin());
            debug(vorov);
            
            area[i] = 0.0;
            vorov.push_back(vorov.front());
            REP (k,SZ(vorov)-1) {
                area[i] -= vorov[k].X*vorov[k+1].Y-vorov[k].Y*vorov[k+1].X;
            }
            area[i] /= 2;
        }

        vector<ll> ans;
        REP (i,n) {
            ans.eb(i);
        }
        sort(ALL(ans),[](const ll &a1,const ll &a2) {
            if (abs(area[a1] - area[a2]) > 1e-4) {
                return area[a1] > area[a2];
            } else {
                return a1 < a2;
            }
        });

        cout << "Case " << cs << ":";
        for (auto an:ans) {
            cout << " " << an+1;
        }
        cout << endl;
    }
    return 0;
}
//Voronoi Diagram