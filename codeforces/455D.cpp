#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<double,double> pdd;
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

const int MOD=1000000007;
const int MAXN=131076;
const int MAXLG=__lg(MAXN)+2;
const int MAXSQ = 300;

int n,tmp,q,cmd,L,R,K;
int cnt[400][MAXN];
deque<int> num[400];
void modi(int l,int r) {
    if(l > r) swap(l,r);

    int lt = num[r/MAXSQ][r-(r/MAXSQ*MAXSQ)];
    cnt[r/MAXSQ][lt]--;
    cnt[l/MAXSQ][lt]++;
    num[r/MAXSQ].erase(num[r/MAXSQ].begin()+r-(r/MAXSQ*MAXSQ));
    num[l/MAXSQ].insert(num[l/MAXSQ].begin()+l-(l/MAXSQ*MAXSQ),lt);

    int blk = l / MAXSQ;
    for (;(blk+1)*MAXSQ-1<r;blk++) {
        int bk = num[blk].back();
        cnt[blk][bk]--;
        cnt[blk+1][bk]++;
        num[blk].pop_back();
        num[blk+1].push_front(bk);
    }
}

void print() {
    vector<int> v;
    REP (i,n) {
        v.eb(num[i/MAXSQ][i%MAXSQ]);
    }
    debug(v);
}
int query(int l,int r,int k) {
    debug(k);
    if (l > r) swap(l,r);
    int ret = 0;

    int lbk = l/MAXSQ+1;
    int rbk = r/MAXSQ-1;
    for (int i=lbk;i<=rbk;i++) {
        ret += cnt[i][k];
    }


    if (l/MAXSQ != r/MAXSQ) {
        for (int i=l;i<n&&i<lbk*MAXSQ-1;i++) {
            if (num[i/MAXSQ][i%MAXSQ] == k) ret++;
        }

        for (int i=r/MAXSQ*MAXSQ;i<n&&i<=r;i++) {
            if (num[i/MAXSQ][i%MAXSQ] == k) ret++;
        }
    } else {
        for (int i=l;i<=r;i++) {
            if (num[i/MAXSQ][i%MAXSQ] == k) ret++;
        }
    }

    return ret;
}

int lastans;
int hssh(int val) {
    return (val+lastans-1)%n;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> tmp;
        cnt[i/MAXSQ][tmp]++;
        num[i/MAXSQ].pb(tmp);
    }

    cin >> q;
    debug(q);
    while (q--) {
        cin >> cmd >> L >> R;
        L = hssh(L), R = hssh(R);
        debug(L,R);
        if (cmd == 1) {
            modi(L,R);
            print();
        } else {
            cin >> K;
            K = hssh(K)+1;
            lastans = query(L,R,K);
            cout << lastans << endl;
        }
    }
    return 0;
}

