#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void trim (vector<int> &vec, int sz) {
    int len = int(vec.size());

    for (int i=0; i<sz; i++) {
        vec[i] = vec[i+(len-sz)];
    }

    vec.resize(sz);
}

int main () {
    cin.tie(0);

    int x, y, a, b, c;
    cin >> x >> y >> a >> b >> c;

    vector<int> p(a), q(b), r(c);

    ll sum = 0;
    for (int i=0; i<a; i++) {
        cin >> p[i];
    }
    for (int j=0; j<b; j++) {
        cin >> q[j];
    }
    for (int k=0; k<c; k++) {
        cin >> r[k];
    }


    sort(p.begin(), p.end());
    sort(q.begin(), q.end());
    sort(r.begin(), r.end());
    trim(p, x);
    trim(q, y);

    for (auto v : p) {
        sum += v;
    }
    for (auto v : q) {
        sum += v;
    }

    p.emplace_back(1000000009);
    q.emplace_back(1000000009);

    for (int i=0, lp=0,rp=0; i<c; i++) {
        if (p[lp] > q[rp]) {

            if (r[c-i-1] > q[rp]) {
                sum -= q[rp];
                sum += r[c-i-1];
                rp++;
            } else {
                break;
            }

        } else {

            if (r[c-i-1] > p[lp]) {
                sum -= p[lp];
                sum += r[c-i-1];
                lp++;
            } else {
                break;
            }

        }

    }
    
    cout << sum << endl;
}
