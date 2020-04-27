#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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

const int MAXN = 100005;
const ll MOD = 1000000007;

int t, n;
string ft, bk;
bool flag;
vector<string> mid;

void check (string nw,string &tg) {
    if (SZ(nw) >= SZ(tg)) {
        if (tg == nw.substr(0, SZ(tg))) {
            tg = nw;
        } else {
            debug(nw, tg);
            flag = false;
        }
    } else {
        if (nw != tg.substr(0, SZ(nw))) {
            flag = false;
            debug(nw, tg);
         }
    }
}
void build (string str) {
    string cf, cb;

    for (auto c : str) {
        if (c == '*') {
            break;
        }
        cf += c;
    }

    for (int i=SZ(str)-1; i>=0; i--) {
        char c = str[i];
        if (c == '*') {
            break;
        }
        cb += c;
    }

    check(cf, ft);
    check(cb, bk);

    string buf;
    for (int i=0; i<=SZ(str); i++) {
        if (i == SZ(str) || str[i] == '*') {
            mid.emplace_back(buf);
            buf = "";
        } else {
            buf += str[i];
        }
    }

}
/*********************GoodLuck***********************/
int main () {
    IOS();


    cin >> t;
    REP1 (tc, t) {

        ft = bk = "";
        mid.clear();
        flag = true;
        cin >> n;
        REP (i, n) {
            string temp;
            cin >> temp;

            build(temp);
        }

        cout << "Case #" << tc << ": ";
        if (flag) {
            cout << ft;
            for (auto tt :mid) {
                cout << tt;
            }
            reverse(ALL(bk));
            cout << bk << endl;
        } else {
            cout << '*' << endl;
        }
    }

}

