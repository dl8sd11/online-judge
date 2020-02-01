#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifdef tmd
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
const __int128 INF = 1e18;

ll hpm, atm, mpe, mpr;

bool solve(__int128 at, __int128 re, __int128 hp, __int128 mp) {
    __int128 round = (hpm + at - 1)/ at;
    if (round * mpe > mp) {
        return false;
    }
    __int128 mp_left = mp - round * mpe;
    __int128 re_max = mp_left / mpr;
    if (re > atm) {
        __int128 die = (re_max * (re-atm) + hp + atm - 1) / atm;
        return die >= round;
    } else {
        __int128 die = (hp + atm - 1) / atm;
        return die >= round;
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    ll at0, re0, hp0, mp0;
    ll atp, rep, hpp, mpp;

    cin >> hpm >> atm;
    cin >> at0 >> re0 >> hp0 >> mp0;
    cin >> atp >> rep >> hpp >> mpp;
    cin >> mpe >> mpr;

    __int128 L = -1, R = INF;
    while (L < R - 1) {
        __int128 mid = (L + R) >> 1;
        if (solve(at0 + mid*atp, re0 + mid*rep, hp0 + mid*hpp, mp0 + mid*mpp)) {
            R = mid;
        } else {
            L = mid;
        }
    }

    if (R == INF) {
        cout << "QQ" << endl;
    } else {
        cout <<ll( R+1 )<< endl;
    }
    return 0;
}
