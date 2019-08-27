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
const ll MAXN = 500005;

vector<int> edge[MAXN];
int t, n, nxt[MAXN], out[MAXN], seg[MAXN * 4], pos[MAXN * 4], tag[MAXN * 4], ans[MAXN];

pii getN (int o) {
    return {tag[o] + seg[o], pos[o]};
}

void push (int o) {
    if (tag[o] != 0) {
        seg[o] += tag[o];
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        tag[o] = 0;
    }
}

void pull (int o) {
    pii ret = min(getN(o<<1), getN(o<<1|1));
    seg[o] = ret.X;
    pos[o] = ret.Y;
}

void build (int o, int l, int r) {
    if (r == l + 1) {
        seg[o] = out[l];
        tag[o] = 0;
        pos[o] = l;
    } else {
        int m = (l + r) >> 1;
        tag[o] = 0;
        build(o<<1, l, m);
        build(o<<1|1, m, r);
        pull(o);
    }
}

pii qry (int qL, int qR, int o = 1, int nL = 0, int nR = n) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return {iNF, -1};
    } else if (qL <= nL && nR <= qR) {
        return getN(o);
    } else {
        int nM = (nL + nR) >> 1;
        push(o);
        return min(qry(qL, qR, o<<1, nL, nM), qry(qL, qR, o<<1|1, nM, nR));
    }
}

void add (int qL, int qR, int val, int o = 1, int nL = 0, int nR = n) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o] += val;
    } else {
        int nM = (nL + nR) >> 1;
        push(o);
        add(qL, qR, val, o<<1, nL, nM);
        add(qL, qR, val, o<<1|1, nM, nR);
        pull(o);
    }

}
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();
    cin >> t;
    while (t--) {
        cin >> n;
        REP (i, n) {
            ans[i] = out[i] = 0;
        }
        priority_queue<int, vector<int>, greater<int> > pq;
        REP (i, n) {
            cin >> nxt[i];

            if (nxt[i] > 0) {
                nxt[i]--;
                edge[nxt[i]].eb(i);
                pq.emplace(nxt[i]);
            }
            
            while (!pq.empty() && pq.top() <= i) {
                pq.pop();
            }
            out[i] = SZ(pq);
        }

        build(1, 0, n);
        pary(out, out+n);

        queue<int> zs;
        zs.emplace(n);

        int id = n + 1;
        while (!zs.empty()) {
            int cur = zs.front();
            zs.pop();

            ans[cur] = id--;
            for (auto v : edge[cur]) {
                add(v, v+1, -1);
            }

            if (nxt[cur] != -1) {
                add(cur+1, nxt[cur], -1);
            }

            while (true) {
                pii ret = qry(0, n);
                if (ret.X == 0) {
                    zs.emplace(ret.Y);
                    add(ret.Y, ret.Y + 1, iNF);
                } else {
                    break;
                }
            }
        }

        if (id == 0) {
            REP (i, n) {
                cout << ans[i] << " \n"[i==n-1];
            }
        } else {
            cout << -1 << endl;
        }

        REP (i, n + 3) {
            edge[i].clear();
        }
    }

    return 0;
}
