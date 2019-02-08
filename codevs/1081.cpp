#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll bit[100003];
int n,m;
void add(int pos,ll val) {
    for (;pos <= n; pos += -pos&pos) {
        bit[pos] += val;
    }
}
ll query (int pos) {
    ll ret = 0;
    for (;pos > 0; pos -= -pos&pos) {
        ret += bit[pos];
    }
    return ret;
}
int main () {
    cin >> n;
    for (int i = 1;i <= n; ++i) {
        ll a;
        cin >> a;
        add(i,a);
        add(i+1,-a);
    }

    cin >> m;
    while (m--) {
        int cmd,a,b;
        ll val;
        cin >> cmd;
        if (cmd == 1) {
            cin >> a >> b >> val;
            add(a,val);
            add(b+1,-val);
        } else {
            cin >> a;
            cout << query(a) << endl;
        }

    }

}