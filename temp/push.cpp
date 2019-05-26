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

const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;
// const int MAXN = 

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

struct State {
    pair<int,int> box[3],me;
    bool operator != (State &s1) {
        REP (i,3) {
            if (box[i] != s1.box[i]) {
                return true;
            }
        }
        return me != s1.me;
    }
};
bool vis[63][63][63][63];
State dp[63][63][63][63];
bool b[9][7];
int n,m;
bool valid(int x,int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}
bool tmpb[9][7],rea[9][7],visd[9][7];
void dfs(int x,int y) {
    visd[x][y] = true;
    rea[x][y] = true;
    REP (i,4) {
        int cx = x + dx[i],cy = y + dy[i];
        if (valid(cx,cy) && !visd[cx][cy] && !tmpb[cx][cy]) {
            dfs(cx,cy);
        }
    }
}

int tran(pair<int,int> p) {
    return p.X*(m+2)+p.Y;
}
vector<pair<int,int> > tg;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,n+2) {
        REP (j,m+2) {
            b[i][j] = true;
        }
    }

    REP1 (i,n) {
        REP1 (j,m) {
            cin >> b[i][j];
        }
    }
    
    State init;
    cin >> init.me.X >> init.me.Y;
    REP (i,3) {
        cin >> init.box[i].X >> init.box[i].Y;
    }
    REP (i,3) {
        pair<int,int> p;
        cin >> p.X >> p.Y;
        tg.emplace_back(p);
    }
    sort(ALL(tg));

    vis[tran(init.me)][tran(init.box[0])][tran(init.box[1])][tran(init.box[2])] = true;
    dp[tran(init.me)][tran(init.box[0])][tran(init.box[1])][tran(init.box[2])].me = {-1,-1};
    queue<State> bfs;
    bfs.emplace(init);

    int cnt = 0;
    State win;
    while (bfs.size()) {

        State cur = bfs.front();
        bfs.pop();
        // debug(cur.me);
        // pary(cur.box,cur.box+3);
        if (++cnt % 1000000 == 0) {
            debug(cnt);
        }  
        vector<pair<int,int> > ma;
        REP (i,3) {
            ma.emplace_back(cur.box[i]);
        }
        sort(ALL(ma));
        if (ma == tg) {
            cout << "WIN" << endl;
            win = cur;
            break;
        }
        REP (i,n+2) {
            REP (j,m+2) {
                tmpb[i][j] = b[i][j];
            }
        }
        REP (i,3) {
            tmpb[cur.box[i].X][cur.box[i].Y] = true;
        }
        MEM(visd,0);
        MEM(rea,0);
        dfs(cur.me.X,cur.me.Y);

        REP (x,3) {
            auto pos = cur.box[x];
            REP (d,4) {
                if (rea[pos.X-dx[d]][pos.Y-dy[d]] && !tmpb[pos.X+dx[d]][pos.Y+dy[d]]) {
                    pair<int,int> nm,nb[3];
                    nm = pos;
                    REP (i,3) {
                        nb[i] = cur.box[i];
                    }
                    nb[x].X += dx[d];
                    nb[x].Y += dy[d];
                    if (!vis[tran(nm)][tran(nb[0])][tran(nb[1])][tran(nb[2])]) {
                        vis[tran(nm)][tran(nb[0])][tran(nb[1])][tran(nb[2])] = true;
                        dp[tran(nm)][tran(nb[0])][tran(nb[1])][tran(nb[2])] = cur;
                        State ns;
                        assert(ns != cur);
                        ns.me = nm;
                        REP (j,3) {
                            ns.box[j] = nb[j];
                        }
                        bfs.emplace(ns);
                    }
                }
            }
        }
    }

    
    while (win.me.X != -1) {
        char c[10][10];
        REP1 (i,n) {
            REP1 (j,m) {
                if (b[i][j]) {
                    c[i][j] = 'E';
                } else {
                    c[i][j] = ' ';
                }
            }
        }
        REP (i,3) {
            c[win.box[i].X][win.box[i].Y] = 'B';    
        }
        c[win.me.X][win.me.Y] = 'M';
        REP1 (i,n) {
            REP1 (j,m) {
                cout << c[i][j];
            }
            cout << endl;
        }
        cout << "................................" << endl;
        debug(win.me);
        pary(win.box,win.box+3);
        win = dp[tran(win.me)][tran(win.box[0])][tran(win.box[1])][tran(win.box[2])];
    }
    return 0;
}

/*
7 5
0 0 1 1 1
0 0 0 0 0
0 0 1 1 0
1 0 0 0 0
1 0 0 0 0
1 0 0 1 0
1 0 0 1 1
6 5
4 4
5 4
5 3
2 5
4 3
4 5
*/