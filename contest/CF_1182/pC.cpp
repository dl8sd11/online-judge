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
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll MAXN = 

ll n;
set<char> vow = {'a','e','i','o','u'};
vector<pair<string,string>> sec,fst;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;

    vector<pair<string,pair<ll,char> > > word(n);
    vector<pair<string,ll> > rem;
    REP (i,n) {
        cin >> word[i].X;
        for (auto c : word[i].X) {
            if (vow.count(c)) {
                word[i].Y.X++;
                word[i].Y.Y = c;
            }
        }
    }
    sort(ALL(word),[&](pair<string,pair<ll,char> > a,pair<string,pair<ll,char> > b) {
        return a.Y < b.Y;
    });
    debug(word);

    REP (i,n) {
        if (i < n-1 && word[i].Y == word[i+1].Y) {
            sec.eb(word[i].X,word[i+1].X);
            i++;
        } else {
            rem.eb(word[i].X,word[i].Y.X);
        }
    }
    debug(rem);

    ll m = SZ(rem);
    REP (i,m) {
        if (i < m-1 && rem[i].Y == rem[i+1].Y) {
            fst.eb(rem[i].X,rem[i+1].X);
            i++;
        }
    }

    if (SZ(sec) > SZ(fst)) {
        cout << SZ(fst) + (SZ(sec) - SZ(fst)) / 2 << endl;
        REP (i,SZ(fst)) {
            cout << fst[i].X << " " << sec[i].X<< endl;
            cout << fst[i].Y << " " << sec[i].Y<< endl;
        }
        for (ll i=SZ(fst); i+1 < SZ(sec); i+=2) {
            cout << sec[i].X << " " << sec[i+1].X << endl;
            cout << sec[i].Y << " " << sec[i+1].Y << endl;
        }
    } else {
        cout << SZ(sec) << endl;
        REP (i,SZ(sec)) {
            cout << fst[i].X << " " << sec[i].X<< endl;
            cout << fst[i].Y << " " << sec[i].Y<< endl;
        }
    }
    return 0;
}
