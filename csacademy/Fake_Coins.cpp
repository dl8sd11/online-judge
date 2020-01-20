#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#define pary(...)
#endif


const int MAXN = 100005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n;

int qry (vector<int> v1, vector<int> v2) {
    cout << "Q " << SZ(v1) << " " << SZ(v2);
    for (auto v : v1) {
        cout << " " << v;
    }
    for (auto v : v2) {
        cout << " " << v;
    }
    cout << endl;

    int ret;
    cin >> ret;

    return ret;
}

void ans (int a10, int a30) {
    cout << "A " << a10 << " " << a30 << endl;
}

int srch (vector<int> v, bool gt) {
    while (v.size() >= 2) {
        vector<int> vl, vr;
        for (int i=0;i<v.size()/2;i++) {
            vl.emplace_back(v[i*2]);
            vr.emplace_back(v[i*2+1]);
        }

        int res = qry(vl, vr);
        if (res == 0) {
            v = {v.back()};
        } else {
            if ((res > 0) ^ gt) {
                v = vr;
            } else {
                v = vl;
            }
        }
    }
    return v.back();
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    int a10, a30;

    vector<int> can;

    if (n & 1) {
        // mind edge case
        int res = qry({1},{n});
        if (res != 0) {
            int r2 = qry({2},{n});

            if (r2 == 0 || res+r2 == 0) {
                if (res > 0) {
                    a30 = 1;
                } else {
                    a10 = 1;
                }
                for (int i=2;i<=n;i++) {
                    can.emplace_back(i);
                }

                if (res > 0) {
                    a10 = srch(can, false);
                } else {
                    a30 = srch(can, true);
                }
            } else {
                if (res > 0) {
                    a10 = n;
                } else {
                    a30 = n;
                }
                for (int i=1;i<n;i++) {
                    can.emplace_back(i);
                }
                if (res > 0) {
                    a30 = srch(can, true);
                } else {
                    a10 = srch(can, false);
                }
            }

            ans(a10, a30);
            return 0;
        } else {
            n--;
        }
    }
    REP1 (i, n) {
        can.emplace_back(i);
    }

    vector<int> ch;
    REP (i, n/2) {
        ch.emplace_back(0);
        ch.emplace_back(1);
    }

    srand(time(0));

    while (true) {
        random_shuffle(ch.begin(),ch.end());
        vector<int> v1, v2;
        REP (i, n) {
            if (ch[i]) {
                v1.emplace_back(can[i]);
            } else {
                v2.emplace_back(can[i]);
            }
        }

        int res = qry(v1, v2);
        if (res > 0) {
            a10 = srch(v2, false);
            a30 = srch(v1, true);
            break;
        } else if (res < 0) {
            a10 = srch(v1, false);
            a30 = srch(v2, true);
            break;
        }
    }

    ans(a10, a30);

}
