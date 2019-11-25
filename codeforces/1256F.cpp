#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 1000006;
const ll MOD = 1000000007;

pair<ll,vector<int>> inv (const string &s) {
    vector<int> cnt(26);
    ll ret = 0;
    for (auto c : s) {
        int cid = c - 'a';
        for (int i=cid+1; i<26; i++) {
            ret += cnt[i];
        }
        cnt[cid]++;
    }
    return {ret, cnt};
}

int mxNum (const vector<int> &cnt) {
    return *max_element(cnt.begin(), cnt.end());
}

bool check (const string &s1, const string &s2) {
    pair<ll,vector<int>> r1 = inv(s1), r2 = inv(s2);
    if (r1.second != r2.second) {
        return false;
    }
    if (max(mxNum(r1.second), mxNum(r2.second)) > 1) {
        return true;
    }
    return (r1.first ^ r2.first ^ 1) & 1;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    int q, n;
    cin >> q;
    while (q--) {
        cin >> n;
        string s1, s2;
        cin >> s1 >> s2;
        if (check(s1, s2)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
