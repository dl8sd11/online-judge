#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll w1,h1,w2,h2;
/********** Good Luck :) **********/
int main()
{
    cin >> w1 >> h1 >> w2 >> h2;
    cout << h1*2 + w1 + 2 + (w1-w2) + h2*2+w2+2 << endl;
    return 0;
}
