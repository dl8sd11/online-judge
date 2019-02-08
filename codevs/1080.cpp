#include <iostream>
#include <assert.h>
using namespace std;
typedef long long ll;

ll bit[100004];
int n,m;
void add(int pos,ll val) {
    for (;pos<=n;pos+=-pos&pos) {
        bit[pos] += val;
    }
}
ll query(int pos) {
    ll ret = 0;
    for (;pos>0;pos-=-pos&pos) {
        ret += bit[pos];
    }
    return ret;
}
int main () {
    cin >> n;
    for (int i=1;i<=n;i++) {
        ll a;
        cin >> a;
        add(i,a);
    }

    cin >> m;
    while (m--) {
        int cmd,a,b;
        cin >> cmd >> a >> b;
        if (cmd == 1) {
            add(a,b);
        } else {
            assert(a <= b);
            cout << query(b) - query(a-1) << endl;
        }
    }
}