#include <bits/stdc++.h>
using namespace std;

int g1,p1,g2,p2;
int main () {
    cin >> g1 >> p1 >> g2 >> p2;
    cout << min(g2-g1,((g2*(p2+1)+99)/100)-1 - ((g1*p1+99)/100)) << endl;
}