#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif


struct SuffixArray {
    string s;
    int n;
    vector<int> sa,rk,hei,t;
    void build(string si) {

        s = si;
        n = SZ(s);
        sa = vector<int>(n, 0);
        rk = vector<int>(n, 0);
        hei = vector<int>(n, 0);
        t = vector<int>(n, 0);
        REP (i,n) {
            rk[sa[i]=i] = s[i];
        }
        t[n-1] = -1;
        for (int h=1;t[n-1] != n-1; h <<= 1) {
            auto cmp = [&](int i,int j) {
                if (rk[i] != rk[j]) {
                    return rk[i] < rk[j];
                } else {
                    return (i+h < n && j+h < n) ? (rk[i+h] < rk[j+h]) : (i > j);
                } 
            };
            sort(ALL(sa),cmp);
            t[0] = 0;
            REP1 (i,n-1) {
                t[i] = t[i-1] + cmp(sa[i-1],sa[i]);
            }
            REP (i,n) {
                rk[sa[i]] = t[i];
            }
        }
        int con = 0;
        REP (i,n) {
            if (rk[i] == 0) {
                hei[0] = con = 0;
            } else {
                if (con) {
                    con--;
                }
                while (s[i+con] == s[sa[rk[i]-1]+con]) {
                    con++;
                }
                hei[rk[i]] = con;
            }
        }
    }
    int operator [] (int idx) {
        return sa[idx];
    }
};


const int MAXN = 400005;

int n, zkw[MAXN*2];

void build () {
    for (int i=n-1; i>0; i--) {
        zkw[i] = min(zkw[i<<1], zkw[i<<1|1]);
    }
}

void chg (int x, int val) {
    for (zkw[x+=n]=val; x>1; x>>=1) {
        zkw[x>>1] = min(zkw[x], zkw[x^1]);
    }
}

int qry (int l, int r) {
    int ret = 0x3f3f3f3f;
    for (l+=n,r+=n; l<r; l>>=1, r>>=1) {
        if (l&1) {
            ret = min(ret, zkw[l++]);
        }
        if (r&1) {
            ret = min(ret, zkw[--r]);
        }
    }
    return ret;
}

SuffixArray sa;
int get_lcp (int i, int j) {
    int ri = sa.rk[i], rj = sa.rk[j];
    if (ri > rj) {
        swap(ri, rj);
    }
    return qry(ri+1, rj+1);
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    string str;
    cin >> str;
    sa.build(str);
    n = SZ(str);

    for (int i=1; i<n; i++) {
        zkw[n+i] = sa.hei[i];
    }
    build();

    int ans = 1;
    for (int i=1;i<=n; i++) {
        for (int j=0; (j+1)*i<n; j++) {
            int lcp = get_lcp(i*j, i*(j+1));
            int rem = i - lcp % i;

            debug(i, j, lcp);
            if (i*j-rem >= 0 && get_lcp(i*j-rem,i*(j+1)-rem) >= i) {
                ans = max(ans, lcp/i+2);
            } else {
                ans = max(ans, lcp/i+1);
            }

        }

    }

    cout << ans << endl;

}

