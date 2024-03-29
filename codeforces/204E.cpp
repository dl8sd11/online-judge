#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#pragma GCC optimize("O3","unroll-loops")
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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
template<typename T> ostream &operator << (ostream &os,pair<T,T> &v){return os<<"("<<v.first<<","<<v.second<<")";}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 200005;
const int MAXLG = __lg(MAXN) + 3;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, k, len;
vector<int> lcp, t;
string str[MAXN], ss;

int sa[MAXN], rk[MAXN];
void build_sa (const string &s) {
    REP (i, len) {
        rk[i] = s[i];
        sa[i] = i;
    }
    for (int h=1;t.back()!=len-1;h<<=1) {
        auto cmp = [&](int i, int j) {
            if (rk[i] != rk[j]) {
                return rk[i] < rk[j];
            } else {
                return (i+h<len&&j+h<len)?rk[i+h]<rk[j+h]:i>j;
            }
        };
        sort(sa,sa+len,cmp);
        for (int i=1;i<len;i++) {
            t[i] = t[i-1] + cmp(sa[i-1],sa[i]);
        }
        REP (i, len) {
            rk[sa[i]] = t[i];
        }
    }
}

void build_lcp (const string &s) {
    int clcp = 0;
    for (int i=0;i<len;i++) {
        clcp = max(clcp-1, 0);
        if (rk[i] == 0) {
            lcp[rk[i]] = 0;
            clcp = 0;
        } else {
            int j = sa[rk[i]-1];
            while (s[i+clcp] == s[j+clcp]) {
                clcp++;
            }
            lcp[rk[i]] = clcp;
        }
    }
}

struct RMQ {
    int dt[MAXLG][MAXN];
    void build () {
        REP1 (p, MAXLG-1) {
            REP (i, len) {
                if (i+(1<<(p-1)) < len) {
                    dt[p][i] = min(dt[p-1][i],dt[p-1][i+(1<<(p-1))]);
                }
            }
        }
    }

    int qry (int l, int r) {
        int L = __lg(r - l);
        return min(dt[L][l],dt[L][r-(1<<L)]);
    }
} lcpMin;


vector<int> spos;
vector<pair<int,int> > ins;
int a[MAXN];
ll ans[MAXN];

struct Node {
    Node *lc, *rc;
    int l, r, sum;
    void pull () {
        sum = lc->sum + rc->sum;
    }
};

Node *root[MAXN];
Node *build (int l, int r) {
    if (r == l + 1) {
        return new Node{0,0,l,r,a[l]};
    } else {
        int m = (l + r) >> 1;
        Node *ret = new Node{build(l,m),build(m,r),l,r,0};
        ret->pull();
        return ret;
    }
}

Node *add (int x, int val, Node *nd) {
    Node *ret = new Node(*nd);
    if (nd->l == nd->r - 1) {
        ret->sum += val;
    } else {
        int mid = (nd->l + nd->r) >> 1;
        if (x >= mid) {
            ret->rc = add(x, val, nd->rc);
        } else {
            ret->lc = add(x, val, nd->lc);
        }
        ret->pull();
    }
    return ret;
}

int qry (int l, int r, Node *nd) {
    if (l == nd->l && r == nd->r) {
        return nd->sum;
    } else {
        int mid = (nd->l + nd->r) >> 1;
        if (l >= mid) {
            return qry(l, r, nd->rc);
        } else if (r <= mid) {
            return qry(l, r, nd->lc);
        } else {
            return qry(l, mid,nd->lc) + qry(mid, r, nd->rc);
        }
    }
}

int qryDiff (int l, int r) {
    return qry(l,r,root[l-1]);
}

int lst[MAXN];

/*********************GoodLuck***********************/
int main () {
    IOS();

    #ifdef test
    n = 2;
    k = 1;
    #else
    cin >> n >> k;
    #endif
    REP (i, n) {
        #ifdef test
        REP (j, 50000) {
            str[i] += 'a' + rand() % 26;
        }
        #else
        cin >> str[i];
        #endif
        ss += "@" + str[i];
        spos.emplace_back(-1);
        REP (j, SZ(str[i])) {
            spos.emplace_back(i);
        }
    }
    len = SZ(ss);
    if (n == 1) {
        if (n == k) {
            len = SZ(str[0]);
            cout << 1LL*len * (len + 1) / 2 << endl;
        } else {
            cout << 0 << endl;
        }
        return 0;
    }
    debug(len);

    lcp.resize(len), t.resize(len);
    build_sa(ss);
    build_lcp(ss);
    debug("HI");

    REP (i, len) {
        lcpMin.dt[0][i] = lcp[i];
    }
    lcpMin.build();

    memset(lst, -1, sizeof(lst));
    REP (i, len) {
        int p = sa[i];
        if (spos[p] != -1) {
            if (lst[spos[p]] == -1) {
//                debug(i);
                a[i] = 1;
            } else {
                ins.emplace_back(lst[spos[p]], i);
            }
            lst[spos[p]] = i;
        }
    }
    sort(ins.begin(), ins.end());

    root[0] = build(0, len);
    int idx = 0;
    REP1 (i, len-1) {
        int cur = -1;
        if (idx<SZ(ins) && ins[idx].first == i) {
            cur = ins[idx].second;
            idx++;
        }
        if (cur == -1) {
            root[i] = root[i-1];
        } else {
            root[i] = add(cur, 1, root[i-1]);
        }
    }
    debug("HI");


    int sum = 0;


    REP (sid, n) {
        sum++;
        REP (i, SZ(str[sid])) {
            sum++;

            int L = 0, R = SZ(str[sid])-i+1;
            while (L < R - 1) {
                int M = (L + R) >> 1;

                int RK = rk[sum-1];
                int LL = 0, LR = RK;
                while (LL < LR - 1) {
                    int LM = (LL + LR) >> 1;
                    if (lcpMin.qry(LM+1, RK+1) >= M) {
                        LR = LM;
                    } else {
                        LL = LM;
                    }
                }

                int RL = len, RR = RK;
                while (RR < RL - 1) {
                    int RM = (RL + RR) >> 1;
                    if (lcpMin.qry(RK+1, RM+1) >= M) {
                        RR = RM;
                    } else {
                        RL = RM;
                    }
                }

                if (qryDiff(LR,RR+1) >= k) {
                    L = M;
                } else {
                    R = M;
                }
            }

            ans[sid] += L;
        }
    }

    debug(double(clock())/CLOCKS_PER_SEC);
    #ifndef test
    REP (i, n) {
        cout << ans[i] << " \n"[i==n-1];
    }
    #endif

}
/*
2 2
oao
od
*/
