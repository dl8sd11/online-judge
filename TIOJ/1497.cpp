#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
typedef pair<ll, ll> pi;
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

const ll INF = (ll)1e18 + 7;
const ll MOD = 1000000007;


string t;
int sa[100003];
int c[100000];   // counting sort array
int temp[2][500000];

void suffix_array()
{
    int N = t.size();             // 字串長度
    int A = 128;            // 字元總類
    int* rank = temp[0];
    int* new_rank = temp[1];

    /* 第一回合：字元個數為1。 */

    // stable counting sort
    // 初始化rank和sa
    for (int i=0; i<A; ++i) c[i] = 0;
    for (int i=0; i<N; ++i) c[rank[i] = t[i]]++;
    for (int i=1; i<A; ++i) c[i] += c[i-1];
    for (int i=N-1; i>=0; --i) sa[--c[t[i]]] = i;

    /* 第二回合以降：字元個數為2，不斷倍增。 */
    pary(sa,sa+N);
    pary(rank,rank+N);
//  for (int m=2; m<=N; m*=2)
    for (int n=1; n<=N*2; n*=2)
    {
        debug(n);
        // counting sort：套用上回合的rank。
        for (int i=0; i<A; ++i) c[i] = 0;
        for (int i=0; i<N; ++i) c[rank[i]]++;
        for (int i=1; i<A; ++i) c[i] += c[i-1];
        debug(c[97],c[98]);
        // 前半段次序：上回合已計算，不必重算。
//      for (int i=N-1; i>=0; --i)
//          sa[--c[rank[i]]] = i;
        // 後半段次序：採用前半段次序，另外考慮空字串。
        int* sa2 = new_rank;        // 借用記憶體、節省記憶體
        debug(N,n);
        pary(rank,rank+N);
        pary(sa,sa+N);
        pary(sa2,sa2+N);
        int r = 0;                  // 名次
        for (int i=N-n; i<N; ++i)   // 空字串，名次最小
            sa2[r++] = i;           // 索引值由小到大排名
        for (int i=0; i<N; ++i)     // 其餘部分等同前半段次序
            if (sa[i] >= n)         // 有前半段，才有後半段
                sa2[r++] = sa[i] - n;
        pary(sa2,sa2+N);
        // counting sort：前半段次序一樣者，按照後半段次序擷取。
        // 本回合的sa
        for (int i=N-1; i>=0; --i)
            sa[--c[rank[sa2[i]]]] = sa2[i];

        // debug(r);
        // pary(rank,rank+N);
        pary(sa,sa+N);
        // 本回合的rank
        new_rank[sa[0]] = r = 0;
        for (int i=1; i<N; ++i)
        {
            // 相異者，排在相異名次；相同者，排在相同名次。
            if (!(rank[sa[i-1]] == rank[sa[i]] &&
                sa[i-1]+n < N &&    // stable sort trick
                rank[sa[i-1]+n] == rank[sa[i]+n]))
                r++;
            new_rank[sa[i]] = r;
        }
        pary(new_rank,new_rank+N);
        swap(rank, new_rank);

        // 如果名次皆相異，表示排序完畢，提早結束演算法。
        if (r == N-1) break;
        // 修正counting sort數值範圍
        A = r + 1;
    }
    for(int i=0;i<N;i++)sa[rank[i]] = i;
}

/********** Main()  function **********/
int main()
{
  IOS();
  getline(cin,t);
  suffix_array();
  pary(sa,sa+t.size());
  REP(i,(t.size())){
    cout<<sa[i]<<endl;
  }
	return 0;
}
