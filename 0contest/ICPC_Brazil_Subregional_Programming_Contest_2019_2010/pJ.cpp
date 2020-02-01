#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 500005;

int n, k;
map<char, int> id;
struct Player {
    int cnt[14];
    bool rec_wc, own_wc;
    Player() :rec_wc(0), own_wc(0){}

    int ck_win () {
        int sum = 0;
        int mx = 0;
        REP1 (i, 13) {
            sum += cnt[i];
            if (cnt[i] > cnt[mx]) {
                mx = i;
            }
        }
        return ((sum+rec_wc+own_wc == 4 && cnt[mx] == 4) ? mx : 100);
    }

    int pk_card () {
        if (own_wc) {
            own_wc = false;
            return -1;
        } else {
            int mn = -1;
            REP1 (i, 13) {
                if (cnt[i] > 0) {
                    debug(i, cnt[i]);
                    if (mn == -1 || cnt[i] < cnt[mn]) {
                        mn = i;
                    }
                }
            }
            cnt[mn]--;
            if (rec_wc) {
                own_wc = true;
                rec_wc = false;
            }
            return mn;
        }
    }
} player[MAXN];
/****GOOD_LUCK****/
int main () {
    IOS();
    for (int i=2;i<=9;i++) {
        id['0'+i] = i;
    }
    id['A'] = 1;
    id['D'] = 10;
    id['Q'] = 11;
    id['J'] = 12;
    id['K'] = 13;

    cin >> n >> k;
    k--;
    player[k].rec_wc = true;
    REP (i, n) {
        REP (j, 4) {
            char c;
            cin >> c;
            debug(id[c]);
            player[i].cnt[id[c]]++;
        }
    }

    int tst = 0;
    while (true) {
        #ifdef tmd
        if (tst++ > 50) {
            break;
        }
        #endif
        int id = -1;
        int win = 100;
        REP (i, n) {
            int tmp = player[i].ck_win();
            if (tmp < win) {
                id = i;
                win = tmp;
            }
        }
        debug(id, win);
        if (id != -1) {
            cout << id + 1 << endl;
            break;
        }
        int cd = player[k].pk_card();
        debug(cd);
        int nxt = (k+1) % n;
        if (cd == -1) {
            player[nxt].rec_wc = true;
        } else {
            player[nxt].cnt[cd]++;
        }
        k = nxt;
    }
    return 0;
}
