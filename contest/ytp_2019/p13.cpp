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

const ll MOD = 20020607;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll MAXN = 
const ll CC = 1000003;
bitset<MOD+10> m;
string t;
queue<pair<ll,string> > q;
ll ans=0,p[35];

bool c(string s){
    if(!(s[0]==s[1]&&s[1]==s[2]&&s[2]==s[3]))return 0;
    if(!(s[4]==s[5]&&s[5]==s[12]&&s[12]==s[13]))return 0;
    if(!(s[6]==s[7]&&s[7]==s[14]&&s[14]==s[15]))return 0;
    if(!(s[8]==s[9]&&s[9]==s[16]&&s[16]==s[17]))return 0;
    if(!(s[10]==s[11]&&s[11]==s[18]&&s[18]==s[19]))return 0;
    if(!(s[20]==s[21]&&s[21]==s[22]&&s[22]==s[23]))return 0;
    return 1;
}

string v1(string s){
    char tmp=s[4];
    s[4]=s[10];s[10]=s[8];s[8]=s[6];s[6]=tmp;
    tmp=s[5];
    s[5]=s[11];s[11]=s[9];s[9]=s[7];s[7]=tmp;
    return s;
}

string v2(string s){
    char tmp=s[0];
    s[0]=s[9];s[9]=s[23];s[23]=s[12];s[12]=tmp;
    tmp=s[1];
    s[1]=s[17];s[17]=s[22];s[22]=s[4];s[4]=tmp;
    return s;
}

string v3(string s){
    char tmp=s[1];
    s[1]=s[7];s[7]=s[21];s[21]=s[18];s[18]=tmp;
    tmp=s[3];
    s[3]=s[15];s[15]=s[23];s[23]=s[10];s[10]=tmp;
    return s;
}

ll hh(string s){
    ll tmp=0;
    REP(i,s.size()){
        tmp+=p[i]*s[i];
        tmp%=MOD;
    }
    return tmp;
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    p[0]=1;
    REP1(i,30)p[i]=p[i-1]*880301%(MOD);
    cin>>t;
    q.push(mp(0,t));
    while(q.size()){
        assert(!q.empty());
        t=q.front().Y;ans=q.front().X;
        q.pop();
        if(c(t)){cout<<ans<<"\n";break;}
        ll h=hh(t);
        if(m[h])continue;
        m[h]=1;
        q.push(mp(ans+1,v1(t)));
        q.push(mp(ans+1,v1(v1(v1(t)))));
        q.push(mp(ans+1,v2(t)));
        q.push(mp(ans+1,v2(v2(v2(t)))));
        q.push(mp(ans+1,v3(t)));
        q.push(mp(ans+1,v3(v3(v3(t)))));
    }
    return 0;
}
