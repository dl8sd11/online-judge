#include <iostream>
using namespace std;
typedef long long ll;

const int MAXN = 200005;
ll bit1[MAXN],bit2[MAXN];
int n,q;
void add(ll *bit,int pos,ll val) {
    for (; pos <= n;pos += -pos&pos) {
        bit[pos] += val;
    }
}

ll query(ll *bit,int pos) {
    ll ret = 0;
    for (; pos > 0;pos -= -pos&pos) {
        ret += bit[pos];
    }
    return ret;
}
int main () {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        ll a;
        cin >> a;
        add(bit1,i,a);
        add(bit1,i+1,-a);
        add(bit2,i,a*i);
        add(bit2,i+1,-a*(i+1));
    }

    cin >> q;
    while (q--) {
        int cmd,a,b;
        ll val;
        cin >> cmd >> a >> b;
        if (cmd == 1) {
            cin >> val;
            add(bit1,a,val);
            add(bit1,b+1,-val);
            add(bit2,a,val*a);
            add(bit2,b+1,-val*(b+1));
        } else {
            cout << (query(bit1,b)*(b+1)-query(bit2,b)) - (query(bit1,a-1)*a-query(bit2,a-1)) << endl;
        }
    }
}