#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define X first
#define Y second
#define eb emplace_back
#define MEM(i,a) memset(i, (a), sizeof(i))
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream& __printRng (ostream& os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg; it!=ed; it++) {
        if (it==bg) os << *it;
        else os << "," << *it;
    }
    return os << "}";
}
template<typename T> ostream& operator << (ostream& os, const vector<T> &v) {return __printRng(os, ALL(v));}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

ostream& operator << (ostream& os, const pii &p) {
    return os << "{" << p.X << "," << p.Y << "}";

}

int n, m;
vector<vector<int> > s, vu, vd;

bool valid (int x, int y) {
    return  (0 <= x && x < n && 0 <= y  && y < m);
}
bool sur (int x, int y, vector<vector<int> > &v) {
    vector<int> dx = {-1, 0, 1, -1, 1, -1, 0, -1};
    vector<int> dy = {-1,-1,-1,0,0,1,1,1,1};
    for (int i=0; i<8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (valid(nx, ny) && v[nx][ny]) {
            return true;
        }
    }
    return false;
}

vector<pii> mu, md;
void st (int x, int y, int id) {
    assert(valid(x, y));
    if (id) {
        md.eb(x, y);
        vd[x][y] = true;
    } else {
        mu.eb(x, y);
        vu[x][y] = true;
    }
}

void rlb () {
    for (auto p : mu) {
        vu[p.X][p.Y] = false;
    }
    for (auto p : md) {
        vd[p.X][p.Y] = false;
    }
}

bool safe = true;
void updu (int x, int y) {
    if (vu[x][y]) return;
    st(x, y, 0);
    queue<pii> bfs;
    bfs.emplace(x, y);
    while (bfs.size()) {
        pii cur = bfs.front();
        bfs.pop();
        int nx = cur.X, ny = cur.Y;
        nx--;
        if (valid(nx, ny) && !vu[nx][ny]) {
            st(nx, ny, 0);
            bfs.emplace(nx, ny);
        }
        nx++;
        ny++;
        if (valid(nx, ny) && !vu[nx][ny]) {
            st(nx, ny, 0);
            bfs.emplace(nx, ny);
        }
        vector<int> dx = {-1, 0, 1, -1, 1, -1, 0, -1};
        vector<int> dy = {-1,-1,-1,0,0,1,1,1,1};
        for (int i=0; i<8; i++) {
            int mx = x + dx[i];
            int my = y + dy[i];
            if (valid(mx, my) && s[mx][my] && !vu[mx][my]) {
                st(mx, my, 0);
                bfs.emplace(mx, my);
            }
        }
    }
}

void updd (int x, int y) {
    if (vd[x][y]) return;
    st(x, y, 1);
    if (vu[x][y]) {
        safe = false;
        return;
    }

    queue<pii> bfs;
    bfs.emplace(x, y);
    while (bfs.size()) {
        pii cur = bfs.front();
        bfs.pop();
        int nx = cur.X, ny = cur.Y;
        nx++;
        if (valid(nx, ny) && !vd[nx][ny]) {
            st(nx, ny, 1);
            if (vu[nx][ny]) {
                safe= false;
                return;
            }
            bfs.emplace(nx, ny);
        }
        nx--;
        ny--;
        if (valid(nx, ny) && !vd[nx][ny]) {
            st(nx, ny, 1);
            if (vu[nx][ny]) {
                safe= false;
                return;
            }
            bfs.emplace(nx, ny);
        }
        vector<int> dx = {-1, 0, 1, -1, 1, -1, 0, -1};
        vector<int> dy = {-1,-1,-1,0,0,1,1,1,1};
        for (int i=0; i<8; i++) {
            int mx = x + dx[i];
            int my = y + dy[i];
            if (valid(mx, my) && s[mx][my] && !vd[mx][my]) {
                st(mx, my, 1);
                if (vu[mx][my]) {
                    safe= false;
                    return;
                }
                bfs.emplace(mx, my);
            }
        }
    }
}
int main () {
    IOS();
    
    cin >> n >> m;
    s.resize(n, vector<int>(m,0));
    vu = vd = s;
    for (int x=0; x<n; x++) {
        for (int y=0; y<m; y++) {
            cin >> s[x][y];
            if (!s[x][y]) continue;
            if (x == 0 || y == m-1 || sur(x,y, vu)) {
                updu(x, y);
            }
            if (y == 0 || x == n-1 || sur(x,y, vd)) {
                updd(x, y);
            }
        }
    }

    int q;
    cin >> q;
    for (int u=0; u<q; u++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        s[x][y] = true;
        mu.clear();
        md.clear();
        safe = true;
        if (x == 0 || y == m-1 || sur(x,y, vu)) {
            updu(x, y);
        }
        if (y == 0 || x == n-1 || sur(x,y, vd)) {
            updd(x, y);
        }
        if (safe) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
            rlb();
        }
    }
}
